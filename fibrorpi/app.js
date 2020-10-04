const express = require('express');
const path = require('path');
const routes = require('./routes/index');
const bodyParser = require('body-parser');
const basicAuth = require('express-basic-auth');


app = express();

// Enable for basic authentication

/* app.use(basicAuth({
      users: { username: 'password' },
      challenge: true // <--- needed to actually show the login dialog!
  })); */

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static('public'));
//app.use(express.static('public\\live'));

app.use('/', routes);


app.get('/listener', function(req, res) {
  res.writeHead(200, {
    'Content-Type': 'text/event-stream',
    'Cache-Control': 'no-cache',
    'Connection': 'keep-alive'
  })
  app.set('listener', res);
  
})


module.exports = app;
