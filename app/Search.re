let component = ReasonReact.statelessComponent("Search");


let make = (~appState: State.state, ~appSend, _children) => {
...component,
render: (_self) =>
                    <div>

                    {ReasonReact.string("Enter your search terms")}
                    <div>
                    <input
                    type_="text"
                     placeholder=""
                     autoFocus=true
                   />
                 </div>
                  <div >
                 <input
                    type_="text"
                    placeholder=""
                    autoFocus=true
                          />
</div>
                          <button className = Styles.actionButton onClick=(_event => appSend(State.SendRequest))> {ReasonReact.string("Submit")} </button>


                 </div>
};
