var RaspiCam = require('raspicam');

exports.takePhoto = function(callback) {
	var opts = {
		w: 1920,
		h: 1080,
		q: 100,
		e: 'jpg',
		mode: 'photo',
		output: '/home/pi/Raspberry/server/images/cam.jpg',
		vf: true,
		hf: true,
		t: 1000
	};
	
	var camera = new RaspiCam(opts);
	
	camera.on("start", function( err, timestamp ) {
		console.log("timelapse started at " + timestamp);
	});
	
	camera.on("stop", function( err, timestamp ) {
		console.log("timelapse child process has been stopped at " + timestamp);
	});
	
	camera.on("exit", function( timestamp ) {
		console.log("timelapse child process has exited");
		camera.stop();
		callback();
	});
	camera.start();
}
