const fs = require('fs');
fs.watch('target.txt', function(){
	console.log("File 'target.txt' just changed!");
})
console.log("Lab 3-3.a.ii by Bennett Moore. Watching target.txt for changes...");
