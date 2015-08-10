var app = angular.module('beeper', []);

app.controller('beeperCtrl', ['$scope', '$http', beepCtrl]);
function beepCtrl($scope, $http) {
	$scope.startBeep = function() {
		$http.get('/beep/start').then(function() {
			console.log('start beeping');
		});
	}

	$scope.stopBeep = function() {
		$http.get('/beep/stop').then(function() {
			console.log('start beeping');
		});
	}
}
