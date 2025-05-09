const express = require('express');
const app = express();
const https = require('https');
const fs = require('fs');

const host = '192.168.31.176';
const port = 3003;

https
  .createServer(
    {
      key: fs.readFileSync('certFiles/privatekey.pem'),
      cert: fs.readFileSync('certFiles/certificate.pem'),
    },
      app.get('/style.css', function (req, res) {
          res.sendFile(process.cwd() + '/style.css');
      }),
      app.get('/script.js', function (req, res) {
          res.sendFile(process.cwd() + '/script.js');
      }),
      app.get('/', function (req, res) {
          res.sendFile(process.cwd() + '/file.html');
      })
  )
  .listen(port, host, function () {
    console.log(`Server listens https://${host}:${port}`);
  });