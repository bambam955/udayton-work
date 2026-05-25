const express = require('express');
const cors = require('cors');
const { MongoClient } = require('mongodb');

const app = express();
const port = process.env.PORT || 8080;

// --- Middleware ---
app.use(cors());
app.use(express.urlencoded({ extended: false }));

// --- MongoDB Connection ---
const mongoUri = "mongodb+srv://mooreb26_user:THCLmaZEWcn8WmHP@mooreb26-messenger-test.xu2oian.mongodb.net/?appName=mooreb26-messenger-test";
const client = new MongoClient(mongoUri);
let db; // Global database reference

(async () => {
    try {
        await client.connect();
        db = client.db("cps449");
        console.log("Connected to the MongoDB cluster - 'cps449' database");

        // Start the server only after the DB connection is successful
        app.listen(port, () => {
            console.log(`HTTP server with Express.js listening on port ${port}`);
        });
    } catch (error) {
        console.error("MongoDB connection error:", error);
        process.exit(1);
    }
})();

// --- Route Definitions ---
app.get('/', (_req, res) => {
    res.send('US City Search Microservice Gateway by Bennett Moore\nVersion: 0.1.0');
});
app.get("/uscities-search", (_req, res) => {
    res.send("US City Search Microservice by Bennett Moore. Usage: URL /uscities-search/:zips(\\d{1,5})");
});

// Common fields projection
const fields = {
    _id: 0,
    city: 1,
    state_id: 1,
    state_name: 1,
    county_name: 1,
    timezone: 1,
    zips: 1
};

app.get('/uscities-search/:zips(\\d{1,5})', async (req, res) => {
    try {
        const zipCode = req.params.zips;
        console.log('/uscities-search/:zips, zip =', zipCode);
        const zipRegex = RegExp(zipCode);
        const data = await db.collection('uscities').find({ zips: zipRegex})
            .project(fields)
            .toArray();
        console.log('ZIP search results:', data);
        res.json(data);
    } catch (error) {
        console.warn('ZIP search error:', error);
        res.status(500).json({ error: 'Internal Server Error' });
    }
});

app.get('/uscities-search/:city', async (req, res) => {
    try {
        console.log('/uscities-search/:city, city =', req.params.city);
        const cityRegex = new RegExp(req.params.city, 'i');
        const data = await db.collection('uscities').find({ city: cityRegex })
            .project(fields)
            .toArray();
        console.log('City search results:', data);
        res.json(data);
    } catch (error) {
        console.error('City search error:', error);
        res.status(500).json({ error: 'Internal Server Error' });
    }
});
