var Gpio = require('onoff').Gpio;
var trig = new Gpio(12, 'out');
//var echo = new Gpio(16, 'in');
trig.writeSync(0);
