let app = require('express')();
let server = require('http').createServer(app);
let io = require('socket.io')(server);

let allSockets = [];

io.on('connection', (socket) => {
    allSockets.push(socket);

    let idTemp = socket.handshake.query.id;

    console.log(`Track de temperatura iniciado ${temp}`);

    socket.join(id);

    socket.on('track', (track) => {
        console.log(`Track temperatura do forno: ${track.tempCentigrados}ºC - ${track.tempFarenheit}ºF | at ${track.at}`);
        io.to(idTemp).emit('track', { track });
    });

    socket.on('disconnet', function(){
        console.log('Disconnected');
        let i = allSockets.indexOf(socket);
        allSockets.splice(i, 1);
    });
});


var port = process.env.PORT || 3001;

server.listen(port, function () {
    console.log('listening in port:' + port);
});