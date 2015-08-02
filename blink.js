var Gpio = require('onoff').Gpio;
var led = new Gpio(17, 'out');

function blink(count) {
	if (count <= 0) {
		return led.unexport();
	}
	led.read(function(err, value) {
		if (err) {
			throw err;
		}
		console.log(value);
		led.write(value ^ 1, function(err) {
			if (err) {
				throw err;
			}
		});
	});
	setTimeout(function() {
		blink(count - 1);
	}, 200);
}

blink(25);
