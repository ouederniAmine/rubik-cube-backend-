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
  origin:'https://rubik-cube-backend.onrender.com', 
  credentials:true,          //access-control-allow-credentials:true
  optionSuccessStatus:200,
}
app.use(cors());
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
  
    const child = spawn("a.exe"); //where a is the exe file generated on compiling the code.
    child.stdin.write(req.body.cube);
    child.stdin.end();
    child.stdout.on("data", (data) => {
      res.setHeader("Access-Control-Allow-Origin", "*")
res.setHeader("Access-Control-Allow-Credentials", "true");
res.setHeader("Access-Control-Max-Age", "1800");
res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.send(data.toString());
    });
  });

app.listen(PORT, () => {
  console.log("running server on port " + PORT);
});

