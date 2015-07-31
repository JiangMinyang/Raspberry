var RaspiCam = require('raspicam');

var opts = {
	w: 1386,
	h: 768,
	q: 100,
	e: 'jpg',
	mode: 'photo',
	output: 'cam.jpg'
};

var camera = new RaspiCa(opts);

camera.start();

camera.on('start', function()) {
	camera.stop();
}