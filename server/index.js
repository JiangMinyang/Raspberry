var Hapi = require('hapi');
var routes = require('./scripts/routes');
var server = new Hapi.Server();
var password = 'jiangminyang';
server.connection({
	port: 80
});

server.route(routes);
server.start(function() {
	console.log('start...');
});
