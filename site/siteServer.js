const express = require('express');
const app = express();
const https = require('https');
const os = require('os');
const fs = require('fs');

const host = getLocalIPv4();
const port = 3003;

function getLocalIPv4() {
    const nets = os.networkInterfaces();
    for (const name of Object.keys(nets)) {
        for (const net of nets[name]) {
            if (net.family === 'IPv4' && net.internal === false) {
                return net.address;
            }
        }
    }
    return '127.0.0.1';
}


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
      }),
      app.get('/hostIP', (req, res) => {
          res.json({ hostIP: `${host}` });
      })
  )
  .listen(port, host, function () {
    console.log(`Server listens https://${host}:${port}`);
  });