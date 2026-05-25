var http = require('http');
var server = http.createServer(httphandler);
var port = process.env.PORT || 8080;
server.listen(port);
console.log('httpserver running at port: ' + port);

function httphandler(req, res) {
    var fs = require('fs'), url = require('url');
    var fullpath = url.parse(req.url, true);
    var localfile = ".." + fullpath.pathname; // files are in parent folder
    console.log("Debug: server's local filename = " + localfile);

    if (fullpath.pathname === "/echo.php") {
        const querystring = require('querystring');
        if (req.method === "GET") {
            console.log("Debug: an HTTP GET request to echo.php");
            var query = querystring.parse(querystring.stringify(fullpath.query));
            console.log("Debug: GET query JSON = " + JSON.stringify(query));
            res.writeHead(200, {'Content-Type': 'text/html'});
            res.write(query.data);
            return res.end();
        }
        else if (req.method === "POST") {
            console.log("Debug: an HTTP POST request to echo.php");
            let postdata = '';
            req.on('data', (chunk) => {postdata += chunk;});
            req.on('end', () => {
                postdata = querystring.parse(postdata);
                console.log("Debug: POST query JSON = " + JSON.stringify(postdata));
                res.writeHead(200, {'Content-Type': 'text/html'});
                res.write(postdata.data);
                return res.end();
            });
        }
        return;
    }

    fs.readFile(localfile, (error, filecontent) => {
        if (error) {
            res.writeHead(404);
            return res.end(fullpath.pathname + " is not found on this server.");
        }
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(filecontent);
        return res.end();
    });
}
