// Typed.js
var typed = $(".typed");
$(function() {
    typed.typed({
        strings: ["Vũ Quang Trọng.",
            "an Embeded Automotive Software Developer.",
            "a Mobile Application Developer too.",
            "a Freelancer, of course.",
            "also a Photographer in my freetime."
        ],
        typeSpeed: 50,
        loop: true,
    });
});

// Back to top button
$(window).scroll(function() {
    if ($(this).scrollTop() > 40) {
        $('.back-to-top').fadeIn('slow');
        $('.main-menu').fadeIn('slow');
    } else {
        $('.back-to-top').fadeOut('slow');
        $('.main-menu').fadeOut('slow');
    }
});
/*
$('.back-to-top').click(function() {
    $('html, body').animate({ scrollTop: 0 }, 1500, 'easeInOutExpo');
    return false;
});
*/