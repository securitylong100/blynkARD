<?php
 define('DB_HOST', 'mysql06.dotvndns.vn');
 define('DB_NAME', 'iottechn_demo'); 
 define('DB_USER','iottechn_admin'); 
 define('DB_PASSWORD','admin1@');

 $con=mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die("Failed to connect to MySQL: " . mysql_error()); 
 $db=mysql_select_db(DB_NAME,$con) or die("Failed to connect to MySQL: " . mysql_error());
 
 function SignIn() 
 { 
 session_start(); 
 
 if(!empty($_POST['user'])) 
 {
$query = mysql_query("SELECT * FROM users where userName = '$_POST[user]' AND pass = '$_POST[pass]'") or die(mysql_error());

 $row = mysql_fetch_array($query) or die(mysql_error()); 
 //if(!empty($row['userName']) AND !empty($row['pass'])) 
 
if( $_POST['pass'] == $row['pass'])
 {
// echo "SUCCESSFULLY LOGIN TO USER PROFILE PAGE..."; 
// echo $_POST['pass'];
 //echo $row['pass'];
?>
<html>
 <a href="http://www.iottechno.com/thuy/api/led/index.html"><strong> <span style="font-size: 32px">Smart Home Mini </span> </strong></a> <br> <br>

  <a href="http://www.iottechno.com/thuy/api/weather/index.html"><strong> <span style="font-size: 32px">Weather Monitor Demo</span> </strong></a>
 </html>
<?php
 }
 else 
 {
 echo "Pass not correct"; 
 }
 }
 
 }
 if(isset($_POST['submit'])) 
 { 
 SignIn(); 
 }
 ?>
 
