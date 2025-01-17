function openPage() {
    window.location.href = "signin.html";}

// Add event listener to the button
document.addEventListener("DOMContentLoaded", () => {
const button = document.getElementById("signin");
button.addEventListener("click", openPage);
});  
// Select all header links
const headerLinks = document.querySelectorAll('.header a');

// Function to set the active class when a link is clicked
headerLinks.forEach(link => {
link.addEventListener('click', function () {
// Remove active class from all links
headerLinks.forEach(item => item.classList.remove('active'));

// Add active class to the clicked link
this.classList.add('active');
});
});


