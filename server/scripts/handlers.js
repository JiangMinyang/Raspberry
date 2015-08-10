var Gpio = require('onoff').Gpio;
var beeper = new Gpio(17, 'out');
var camera = require('./camera');
var password = 'jiangminyang';
exports.startBeep = function(request, response) {
	beeper.write(1, function(err) {
		if (err) {
			return console.log(err);
		}
		response('stop succeed', 200);
	});
}

exports.stopBeep = function(request, response) {
	beeper.write(0, function(err) {
		if (err) {
			return console.log(err);
		}
		response('stop succeed', 200);
	});
}

exports.takePhoto = function(request, response) {
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
