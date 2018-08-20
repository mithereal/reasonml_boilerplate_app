open State;


let component = ReasonReact.reducerComponent("App");
let make = _children => {
  ...component,
  initialState: () => {
          value: "string",
    },
    reducer,
  render: ({state, send}) =>
    <div className=Styles.app>
       <Topbar />
       <Search appState=state appSend=send/>
    </div>,
};
