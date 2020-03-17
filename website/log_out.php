<?php
// Initialize the session
session_start();
 
// Unset all of the session variables
$_SESSION = array();
 
// Destroy the session.
session_destroy();
 
// Redirect to login page

echo "<script>
alert('You have successfully logged out');
window.location.href='adminlogin.php';
</script>";

exit;
?>

