const express = require('express');
const app = express();
var port = process.env.PORT || 8080; // important for deployment later
app.use(express.static('static'));
app.use(express.urlencoded({extended: false}));
app.listen(port, () => console.log('Express server running on port ' + port));

app.get('/', (req, res) => {
    res.sendFile(`${__dirname}/static/form.html`);
});
app.get('/echo.php', (req, res) => {
    res.send(req.query.data);
});
app.post('/echo.php', (req, res) => {
    res.send(req.body.data);
});
