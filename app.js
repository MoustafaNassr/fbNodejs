'use strict';

const express = require('express');
const app = express();
const url = require('url');
const admin = require('firebase-admin');

// Initialize Firebase Admin SDK using service account
const serviceAccount = require('/Users/moustaphanassr/Downloads/fire.json');

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: 'https://gyro-bbcfe-default-rtdb.europe-west1.firebasedatabase.app/' // Replace with your Firebase Realtime Database URL
});

// Realtime Database instance
const db = admin.database();

// Route handler for root URL
app.get('/', (req, res) => {
  const q = url.parse(req.url, true);
  if (q.search != null) {
    const dataa = {
      moisture: q.search.split('=')[1]
    };
    db.ref('sensorData').set(dataa)
      .then(() => console.log('New sensor data written to database'));

    // Display the moisture value on the web page
    res.status(200).send(`Moisture value: ${dataa.moisture}`).end();
  } else {
    res.status(200).send('No moisture value provided.').end();
  }
});

// Start the server
const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
  console.log(`App listening on port ${PORT}`);
  console.log('Press Ctrl+C to quit.');
});

module.exports = app;
