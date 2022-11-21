const express = require("express");
const cors = require("cors");
const { exec, spawn } = require("child_process");

const bodyParser = require("body-parser");
const cookieParser = require("cookie-parser");
const session = require("express-session");

const PORT = 3001;
const app = express();

app.use(express.json());
app.use(cors())
app.use(cookieParser());
app.use(bodyParser.urlencoded({ extended: false }));
app.use( bodyParser.json() );       // to support JSON-encoded bodies



app.post("/cubePieces", (req, res) => {
  ;
  
  execFile('a.exe', ['wwwwwwwwwrorrrrrrryyyyyyyyyooooooorogggggbgggbbbgbbbbb'], function(err, data) {
    if(err) {
        res.send(err)
    } 
    else 
    res.send(data.toString())
}); 
});

app.post("/CubeSolutions", (req, res) => {
  exec("gcc cube.c", (error, stdout, stderr) => {
    if (error) {
      console.log(`error: ${error.message}`);
      return;
    }
    if (stderr) {
      console.log(`stderr: ${stderr}`);
      return;
    }
  
    const child = spawn("./a.exe"); //where a is the exe file generated on compiling the code.
    child.stdin.write(req.body.cube);
    child.stdin.end();
    child.stdout.on("data", (data) => {
      res.send(data.toString());
    });
  });
});







app.listen(PORT, () => {
  console.log("running server on port " + PORT);
});
