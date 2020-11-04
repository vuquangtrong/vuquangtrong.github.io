var typed = $(".typed");
$(function() {
    typed.typed({
        strings: ["Vũ Quang Trọng",
            "an Automotive Software Engineer",
            "a Mobile Application Developer",
            "a Photographer",
            "a Freelancer",
        ],
        showCursor: false,
        typeSpeed: 20,
        backSpeed: 0,
        backDelay: 1000,
        loop: true,
    });
});

// Back to top button
var backToTop = $('#back-to-top');

$(window).scroll(function() {
  if ($(window).scrollTop() > 100) {
    backToTop.addClass('show');
  } else {
    backToTop.removeClass('show');
  }
});

backToTop.on('click', function(e) {
  e.preventDefault();
  $('html, body').animate({scrollTop:0}, '1000');
});
