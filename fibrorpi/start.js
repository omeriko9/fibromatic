const app = require('./app');
const https = require('https');
const fs = require('fs')


options = {};
// Uncomment below for HTTPS and supply key & crt files

/* 
var key = fs.readFileSync(__dirname + '/certs/noise.key');
var cert = fs.readFileSync(__dirname + '/certs/noise.crt');
var options = {
  key: key,
  cert: cert
};
*/ 

//httpsport = 443; //3001;
portnumber = 3000;

const server = app.listen(portnumber, () => {
  console.log(`Express is running on port ${server.address().port}`);
});

// Uncomment below for HTTPS

/* 
var serverhttps = https.createServer(options, app);

serverhttps.listen(httpsport, () => {
  console.log("server https starting on port : " + httpsport)
});
*/
