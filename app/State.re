[@bs.module "phoenix"]


type state = {
  value: string
};


type websocket = {
id: string
}


type action =
 | SendRequest
 | Add


open Phx


let handleReiceive = (event, any) =>
  switch event {
  | "ok" => Js.log(("handleReiceive:" ++ event, "Joined"))
  | "error" => Js.log(("handleReiceive:" ++ event, "Failed to join channel"))
  | _ => Js.log(("handleReiceive:" ++ event))
  };

let handleEvent = (event,  response) =>
 switch event {
  | "testevent" => /* im trying to send this with send but not working because i want the response value to update the state value:*/
  Js.log(("handleEvent:" ++ event, response))
  | _ => Js.log(("handleReiceive:" ++ event))
};

let handleSyncState = (response) => {
  let _ = Js.log(("handleSyncState", response));
  /*let _ = Js.log (Array.iter (fun key -> Js.log (Js_dict.unsafeGet response key)) (Js_dict.keys response) ) in*/
  let _presences = Presence.syncState(Js.Dict.empty(), response);
  ();
};

let handleSyncDiff = (diff) => {
  let _ = Js.log(("handleSyncDiff:diff", diff));
  let presences = Presence.syncDiff(Js.Dict.empty(), diff);
  let _ = Js.log(("handleSyncDiff:presences", presences));
  ();
};

let socket = initSocket("/socket") |> connectSocket |> putOnClose(() => Js.log("Socket closed"));

let decode = (websocket) =>
        Json.Decode.{
          id: websocket |> field("id", string)
        };


let join = (channel) =>
{

  let _ =
    channel
    |> putOn("testevent", handleEvent("testevent"))
    |> putOnSyncState(handleSyncState)
    |> putOnsyncDiff(handleSyncDiff)
    |> joinChannel
    |> putReceive("ok", handleReiceive("ok"))
    |> putReceive("error", handleReiceive("error"))
    |> putReceive("quote", handleReiceive("error"))

};


let request = (hash) =>
{
  let payload = Js.Dict.empty();
    Js.Dict.set(payload, "id", Js.Json.string(hash));


    Js.Promise.(
      Fetch.fetchWithInit(
        "/query",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
          ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          ()
        )
      )
      |> then_(Fetch.Response.json)

    )
    |> ignore;
};

  /* makes a post request with the following json payload { query: "what is wrong with me" } */
  let send = (q) => {

    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "query", Js.Json.string(q));

    Js.Promise.(
      Fetch.fetchWithInit(
        "/",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
          ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          ()
        )
      )
      |> then_(Fetch.Response.json)
      |> then_(json => {

            let websocket = json |> decode;
            let ch = "query:" ++ websocket.id;
            let channel = socket |> initChannel(ch);

            join(channel);
                request(websocket.id);
                Js.Promise.resolve();

              })
    )
    |> ignore;
    };



let reducer = (action, state) =>
  switch(action) {
  | SendRequest => send(state.value);
  ReasonReact.Update({...state, value: "null"})
  
 };

