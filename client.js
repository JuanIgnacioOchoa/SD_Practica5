var readline = require('readline');
var dgram = require('dgram');


var PORT = 9930;
var HOST = '192.168.1.34';



var client = dgram.createSocket('udp4');

client.on('listening', function () {
    var address = client.address();
    //console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

client.on('message', function (message, remote) {

    console.log(' ' + message);

});

var rl = readline.createInterface(process.stdin, process.stdout);
var init = true;
rl.setPrompt('Ingresar nickname> ');
rl.prompt();
rl.on('line', function(line) {
    if(init == true) {
        var message = new Buffer('*' + line);
        init = false;
    } else {
        var message = new Buffer(line);
    }
    client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
        if (err) throw err;
        //console.log('UDP message sent to ' + HOST +':'+ PORT);
       
    });
    
}).on('close',function(){
    process.exit(0);
    
});
