var Hapi = require('hapi');
var camera = require('./scripts/camera');
var server = new Hapi.Server();
var password = 'jiangminyang';
server.connection({
	port: 80
});

server.route({
	method: 'GET',
	path: '/photo',
	handler: function(request, response) {
		var query = request.query;
		if (query.key === undefined || query.key !== password) {
			response('invalid key', 404);
			return;
		}
		console.log('hello');
		camera.takePhoto(function() {
			response.file('./partials/photo.html');
		});
	}
});
server.route({
	method: 'GET',
	path: '/{name}',
	handler: function(request, response) {
		response.file('./' + request.params.name);
	}
});
server.start(function() {
	console.log('start');
});
