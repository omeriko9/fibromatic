const express = require('express');
const router = express.Router();

arduinoSerial = '/dev/ttyS0';


router.get('/', (req, res) => {
  res.render('index', {title:'Fibromatic'});
});


SerialPort = require('serialport');
port = new SerialPort(arduinoSerial, { baudRate: 19200 });

router.get('/act', (req, res) => {

  console.log("Acting");
  console.log(req.query);
 
  name = req.query.name;

  toSend = "";
  if (name == "start")
  {
    toSend = "p011";
    port.write("406000200\n");
  }
  if (name == "start2")
  {
    toSend = "t011";
    port.write("406000200\n");
  }
  if (name == "stop")
  {
    port.write("i000\n");
    toSend = "p010";
  }

  if (name=="1")  { toSend = "406000150"; }
  if (name=="2")  { toSend = "406000080"; }
  if (name=="3")  { toSend = "406000040"; }
  if (name=="4")  { toSend = "406000001"; }

  if (name=="up") { toSend = "o011"; }
  if (name=="down") { toSend = "o010"; }

  if (name=="enlarge") { toSend = "m000"; }
  if (name=="reduce") { toSend = "n000"; }

  if (name == "custom") {
     port.write(req.query.value + '\n');
     res.send('ok');
     return;
  }

  
  port.write(toSend+ '\n');
  res.send('ok');

  return;

});

module.exports = router;