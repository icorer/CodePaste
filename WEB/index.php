<?php
	if(isset($_GET['link'])&&isset($_GET['type'])){
		$_GET['link']="./save_code_doc/".$_GET['link'];
		if($_GET['type']=="public")
			$_GET['link'].=".html";
		else if($_GET['type']=="private")
			$_GET['link'].=".php";
		else
			print "View Error！";
		if(($_GET['type']=="public")||($_GET['type']=="private"))
		{
			if(file_exists($_GET['link']))
				include($_GET['link']);
			else
				print "<script>alert(\"Error: Do not have this codes\")</script>";
		}
			
	}
?>