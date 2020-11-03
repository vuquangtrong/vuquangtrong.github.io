var typed = $(".typed");
$(function() {
    typed.typed({
        strings: ["Vũ Quang Trọng",
            "an Embeded Automotive Software Engineer",
            "a Mobile Application Developer",
            "a Photographer",
            "a Freelancer",
        ],
        typeSpeed: 20,
        backSpeed: 0,
        backDelay: 1000,
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
