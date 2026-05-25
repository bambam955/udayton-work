const express = require('express');
const app = express();
var port = process.env.PORT || 8080; // important for deployment later
app.use(express.static('static'));
app.use(express.urlencoded({extended: false}));
const httpServer = require("http").createServer(app);
const { Server } = require("socket.io");
const io = new Server(httpServer, { cors: { origin: "*"} });
httpServer.listen(port, () => console.log('Express-http-socket.io server running on port ' + port));

app.get('/', (req, res) => {
    res.sendFile(`${__dirname}/static/form.html`);
});
app.get('/echo.php', (req, res) => {
    res.send(req.query.data);
});
app.post('/echo.php', (req, res) => {
    res.send(req.body.data);
});

io.on('connection', (socketclient) => {
    console.log('A new client is connected!');
    socketclienthandler(socketclient)
});

function socketclienthandler(socketclient){
    socketclient.on('message', (data) => {
        console.log('Data from a client:', data);
        io.emit("message", `${socketclient.id} says: ${data}`);
    });
}
