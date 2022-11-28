const express = require("express");
const cors = require("cors");
const { exec, spawn } = require("child_process");

const bodyParser = require("body-parser");
const cookieParser = require("cookie-parser");
const session = require("express-session");
const {c} = require('compile-run');

const PORT = process.env.PORT|| 3001;
const app = express();

app.use(express.json());
const corsOptions ={
  origin:false, 
  credentials:true,          //access-control-allow-credentials:true
  optionSuccessStatus:200,
}
app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*"); // or specify your domain i.e. https://localhost.com
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
  }); I
app.use(cookieParser());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json()); // to support JSON-encoded bodies

app.post("/cubePieces", (req, res) => {
  execFile(
    "a.exe",
    ["wwwwwwwwwrorrrrrrryyyyyyyyyooooooorogggggbgggbbbgbbbbb"],
    function (err, data) {
      if (err) {
        res.send(err);
      } else res.send(data.toString());
    }
  );
});

// get endpoint hello server
app.get("/", (req, res) => {
  res.setHeader("Access-Control-Allow-Origin", "*")
res.setHeader("Access-Control-Allow-Credentials", "true");
res.setHeader("Access-Control-Max-Age", "1800");
res.setHeader("Access-Control-Allow-Headers", "content-type");
  res.send("Hello Server");
});
app.post("/CubeSolutions", (req, res) => {
  c.runFile('./src/cube.c', { stdin:'3\n2 '}, (err, result) => {
    if(err){
        console.log(err);
    }
    else{
        res.send(result.stdout);
    }
});
 
});

app.listen(PORT, () => {
  console.log("running server on port " + PORT);
});

