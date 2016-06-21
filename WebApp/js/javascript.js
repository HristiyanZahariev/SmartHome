function getIp() {
	var url = "http://" + document.getElementById('espIp').value; + ":80/";

	$(document).ready(function() {
		$(".led").click(function() {
			var p = $(this).attr('id');
			console.log(p);
			$.get(url, {pin:p});
		});
	});
}

function change(button_id) {
	var el = document.getElementById(button_id);
	if (el.firstChild.data == "On") {
		el.firstChild.data = "Off";
		var state = document.getElementById("state").innerHTML;
		state += "<p>";
		state = "Shut it down"
		state += "</p>";
		document.getElementById("state").innerHTML = state;
	}
	else {
 	el.firstChild.data = "On";
	var state = document.getElementById("state").innerHTML;
	state += "<p>";
	state = "Power it up"
	state += "</p>";
	document.getElementById("state").innerHTML = state;
	}
}