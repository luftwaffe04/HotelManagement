$(function() {
	var MOBILE_CLICKED = 0;
	$(".mobile img").click(function(event) {
		/* Act on the event */
		if(!MOBILE_CLICKED) {
			// open Menu
			MOBILE_CLICKED = 1;
			$(".mobile img").css({
				transform: 'rotate(90deg)',
				transition: 'transform 0.5s'
			});
			$("#header nav ul").css({
				height: '100%'
			});
		}
		else {
			MOBILE_CLICKED = 0;
			$(".mobile img").css({
				transform: 'rotate(0deg)',
				transition: 'transform 0.5s'
			});
			$("#header nav ul").css({
				height: '0'
			});
		}
	});

	$("li.findhotel").click(function(event) {
		/* Act on the event */
		event.preventDefault();
		$("#findhotel").css('display', 'block');
	});

	$("#findhotel .wrap section p.cancel").click(function(event) {
		event.preventDefault();
		$("#findhotel").css('display', 'none');
	});
});
