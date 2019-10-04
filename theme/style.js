/* 
 * Theme for <Code/theHeck> blog
 * vuquangtrong.github.io
 */

// scroll functions
$(window).scroll(function(e) {
    // add/remove class to navbar when scrolling to hide/show
    var scroll = $(window).scrollTop();
    if (scroll >= 150) {
        $('.navbar').addClass("navbar-hide");
        // force to hide expanded navbar
        $('#navbarMenu').collapse('hide');
    } else {
        $('.navbar').removeClass("navbar-hide");
    }
});