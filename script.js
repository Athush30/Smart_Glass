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
// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.20.0/firebase-app.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration here (Do not use the existing configuration)
const firebaseConfig = {
    apiKey: "AIzaSyAlwyZHvR3p4GYPqTJYz-eWTT09vP0ooZ8",
    authDomain: "projectx-ebe0f.firebaseapp.com",
    databaseURL: "https://projectx-ebe0f-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "projectx-ebe0f",
    storageBucket: "projectx-ebe0f.firebasestorage.app",
    messagingSenderId: "543814439424",
    appId: "1:543814439424:web:8d146caf1400769f867ee5"
    };

// Initialize Firebase
firebase.initializeApp(firebaseConfig);


// getting reference to the database
var database = firebase.database();

//getting reference to the data we want
var dataRef2 = database.ref('act_height');

//fetch the data

dataRef2.on('value', function(getdata2){
  let act_height = getdata2.val();
  document.getElementById('act_height').innerHTML = act_height ;
})
if (temp == true){
   dataRef2.on('value', function(getdata2){
  var temp = getdata2.val();
  document.getElementById('act_height').innerHTML = "22" ;
})

}
var dataRef2 = database.ref('connection status');

//fetch the data

dataRef2.on('value', function(getdata2){
  let connection_status = getdata2.val();
  document.getElementById('connection status').innerHTML = connection_status ;
})
if (temp == true){
   dataRef2.on('value', function(getdata2){
  var temp = getdata2.val();
  document.getElementById('connection status').innerHTML = "22" ;
})

}

