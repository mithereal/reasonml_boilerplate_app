
/*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
open Css;

let card = style([
display(flexBox),
flexDirection(column),
alignItems(stretch),
backgroundColor(white),
boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.3)),

]);
let header = style([
display(flexBox),
flexDirection(column),
alignItems(stretch),
backgroundColor(white),
boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.3)),

]);


let title = style([
fontSize(rem(1.5)),
margin(auto),
]);

let app = style([
fontSize(rem(1.5)),
background( darkgray ),
height(vh(100.)),
]);

let actionButton = disabled =>
style([
background(disabled ? darkgray : white),
color(black),
border(px(1), solid, black),
borderRadius(px(3)),
])
