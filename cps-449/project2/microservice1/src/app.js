const express = require('express');
const app = express();
const cors = require('cors');
const { getHonors } = require('./honors');

// App factory module: middleware and route definitions are kept here, while index.js only boots the server.
app.use(express.urlencoded({extended: false}));
app.use(express.json());
app.use(cors());

app.get('/', (_req, res) => {
    // Basic health/info endpoint for a quick sanity check.
    res.send('<html><head><title>Academic Honors Microservice</title></head><body><h3>Academic Honors Microservice by Bennett Moore</h3><p>Version: 1.0.0</p></body></html>');
});

app.get('/honors/:gpa', (req, res) => {
    const { gpa } = req.params;
    const { credits } = req.query;

    const payload = getHonors(gpa, credits);
    if (payload.error) {
        return res.status(400).json({ error: payload.error });
    }

    res.json(payload);
});

app.post('/honors', (req, res) => {
    const { gpa, creditHours } = req.body || {};

    if (gpa === undefined || creditHours === undefined) {
        return res.status(400).json({ error: 'Payload must include gpa and creditHours.' });
    }

    const payload = getHonors(gpa, creditHours);
    if (payload.error) {
        return res.status(400).json({ error: payload.error });
    }

    res.json(payload);
});

module.exports = app;
