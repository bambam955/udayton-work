const app = require('./src/app');

// Resolve listen port from environment so the service can run in different environments.
const port = process.env.PORT || 8080;

// Thin bootstrap layer: start the imported Express app.
app.listen(port, () => console.log('HTTP server listening on port ' + port));
