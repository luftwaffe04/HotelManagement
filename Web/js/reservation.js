var SELECTED_ROOM = 0;
var SELECTED_HOTEL = 0;
var CHKIN_DATE = 0;
var CHKOUT_DATE = 0;
var PERSONNEL = 0;

// ----------- READY FUNCTION ---------------------------
$(function() {
	$.Init();
	// Room Button CLICK EVENT -----------------------------------------------
	$("#reserve .hotelroom section p").click(function(event) {
		/* 방 번호를 클릭했을 때 발생하는 이벤트 처리 */
		var get_class = $(this).attr("class");
		var where_am_i = $("#reserve .hotelroom section p");

			if(get_class === "unchked") {
				// 미선택을 클릭한 경우 선택됨 부여
				where_am_i.removeClass('chked');
				where_am_i.addClass('unchked');
				$(this).removeClass();
				$(this).addClass('chked');
				var room_no = $(this).html();
				SELECTED_ROOM = parseInt(room_no);
				// rommdetail의 p를 변경한다
				$(".roomdetail>section>p").html("Room "+room_no);
			}
			else if(get_class === "chked") {
				// 선택됨을 클릭한 경우 미선택을 부여
				$(this).removeClass('chked');
				$(this).addClass('unchked');
				// rommdetail의 p를 원래대로 돌린다
				$(".roomdetail>section>p").html("Room");
			}
	});

	// .roomdetail PLUS Button CLICK EVENT -----------------------------------
	$(".roomdetail #room1 .plus").click(function(event) {
		/* 호텔 인원 증가 버튼을 클릭했을 때 발생하는 이벤트 처리 */
		var person = $(".roomdetail #room1 .person");
		if(PERSONNEL < 4) {
			PERSONNEL++;
			person.html(PERSONNEL);
		}
		else {
			alert("Only 4 people or less can be booked per room.");
		}
	});

	// .roomdetail MINUS Button CLICK EVENT ----------------------------------
	$(".roomdetail #room1 .minus").click(function(event) {
		/* 호텔 인원 증가 버튼을 클릭했을 때 발생하는 이벤트 처리 */
		var person = $(".roomdetail #room1 .person");
		if(PERSONNEL > 0) {
			PERSONNEL--;
			person.html(PERSONNEL);
		}
	});

	$(".roomdetail p.submit").click(function(event) {
		/* submit 버튼을 누르면 결과 확인 창을 띄우는 이벤트 */
		CHKIN_DATE = $("#in_date").val();
		CHKOUT_DATE = $("#out_date").val();

		if(!SELECTED_ROOM) {
			alert("Please select a room to reserve.");
			return;
		}
		else if(!CHKIN_DATE) {
			alert("Please select a check-in date.");
			return;
		}
		else if(!CHKOUT_DATE) {
			alert("Please select a check-out date.");
			return;
		}
		else if(!PERSONNEL) {
			alert("Please select the number of people to reserve.");
			return;
		}
		else {
			$(".aftersubmit form .rno input#rno").val(SELECTED_ROOM);
			$(".aftersubmit form .chkin input#chkin").val(CHKIN_DATE);
			$(".aftersubmit form .chkout input#chkout").val(CHKOUT_DATE);
			$(".aftersubmit form .pers input#pers").val(PERSONNEL);
			$(".aftersubmit").css('display', 'block');
		}
	});

	$(".aftersubmit #cancel").click(function(event) {
		/* Aftersubmit에서 취소버튼을 누른 경우 */
		$(".aftersubmit").css('display', 'none');
	});

	setInterval(function() {$.Init();}, 1000);
});

$.Init = function() {
	$.ajax({
		url: './phpclass/getdata.php'
	})
	.done(function(data) {
		console.log("success");
		$("").text(data);
		var temp = data.split('_');
		var already = temp[0].split(',');
		var unchked = temp[1].split(',');

		var i = 0;
		while(1) {
			if(already[i] === "") break;
			$("#"+already[i]).removeClass();
			$("#"+already[i]).addClass('already');
			i++;
		}
		i = 0;
		while(1) {
			if(unchked[i] === "") break;
			var wami = $("#"+unchked[i]).attr("class");
			if(wami != "chked") {
				$("#"+unchked[i]).removeClass();
				$("#"+unchked[i]).addClass('unchked');
			}
			i++;
		}
	})
	.fail(function() {
		console.log("error");
	});
}
