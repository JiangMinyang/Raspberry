var handler = require('./handlers');
module.exports = [{
	method: 'GET',
	path: '/photo',
	handler: handler.takePhoto
}, {
	method: 'GET',
	path: '/images/{name}',
	handler: function(request, response) {
		response.file('./images/' + request.params.name);
	}
}, {
	method: 'GET',
	path: '/scripts/{name}',
	handler: function(request, response) {
		response.file('./scripts/' + request.params.name);
	}
}, {
	method: 'GET',
	path: '/beep/start',
	handler: handler.startBeep
}, {
	method: 'GET',
	path: '/beep/stop',
	handler: handler.stopBeep
}, {
	method: 'GET',
	path: '/beep',
	handler: function(request, response) {
		response.file('./partials/index.html');
	}
}];
