const express = require('express');
const cors = require('cors');

const chatRoutes = require('./chat-routes');

// Express app factory module: keeps middleware and route wiring together.
const app = express();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.get('/', (_req, res) => {
  res.send('<html><head><title>LLM Chat Microservice</title></head><body><h3>LLM Chat Microservice by Bennett Moore</h3><p>Version: 0.3.0</p></body></html>');
});

app.use('/', chatRoutes);

module.exports = app;
