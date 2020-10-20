var HAMBURGER_STATE = 0; // 0일때 누르면 열림
var HEADER_WIDTH = 0;

$(function() {
	HEADER_WIDTH = $("#header").width();

	// Hamburger Click Event
	$(".hamburger").click(function(event) {
		/* Act on the event */
		if(HAMBURGER_STATE == 0) {
			// Open Sidebar
			HAMBURGER_STATE = 1;
			$(".hamburger").css({
				transform: 'rotate(90deg)',
				transition: 'transform 0.5s'
			});

			$("#header").css({
				left: '0px',
				transition: 'all 0.5s'
			});
		}
		else {
			// Close Sidebar
			HAMBURGER_STATE = 0;
			$(".hamburger").css({
				transform: 'rotate(0deg)',
				transition: 'transform 0.5s'
			});

			$("#header").css({
				left: -HEADER_WIDTH+'px',
				transition: 'all 0.5s'
			});
		}
	});

	var img_index = 2;
	setInterval(function() {
		$("#mainImage").fadeOut(1000, function() {
			$(this).css("background-image", "url('./img/hotel"+img_index+".jpg')");
			$(this).fadeIn(1000);
		});

		img_index++;

		if(img_index > 9) {
			img_index = 1;
		}
	}, 6000);


});
