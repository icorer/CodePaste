<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
		<link rel="stylesheet" href="css/normalize.css">
		<link rel="stylesheet" href="css/style.css" media="screen" type="text/css" />
		<title>pass_codes_pages_title</title>
		<style>
			ptitle{
				color:#00529B;
				font-size: 20px;
			}
			h1{
				color: #331804;
			}
			hr{
				color:#DBEAF9;
			}
			a:link,a:visited{
			 text-decoration:none;  
			}
			a:hover{
			 color: red;
			}
		</style>
		<script type="text/javascript" src="http://icode.qiniudn.com/shCore.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushBash.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushCpp.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushCSharp.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushCss.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushDelphi.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushDiff.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushGroovy.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushJava.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushJScript.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushPhp.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushPlain.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushPython.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushRuby.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushScala.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushSql.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushVb.js"></script>
		<script type="text/javascript" src="http://icode.qiniudn.com/shBrushXml.js"></script>
		<link type="text/css" rel="stylesheet" href="http://icorer.com/styles/shCore.css"/>
		<link type="text/css" rel="stylesheet" href="http://icorer.com/styles/shThemeDefault.css"/>
		<script type="text/javascript">
			SyntaxHighlighter.config.clipboardSwf = 'http://icorer.com/styles/clipboard.swf';
			SyntaxHighlighter.all();
		</script>
	</head>
<body <?php show_html("body");  ?>>
		<section class="webdesigntuts-workshop" style="display:<?php show_html("input_password");?>;">
			<form action="" method="get"  >		    
				<input type="password" title="�����������" name="password" placeholder="Password">		    	
			    <input type="hidden" name="link" value="pass_file_link_number" />
			    <input type="hidden" name="type" value="private" />
				<button >�鿴����</button>
			</form>
		</section>
		
	
		<center>
		 <div style="width:80%;height:90%;" >
		 <?php
			$password_admin=md5("default_password"); //��̨�洢������
			if(isset($_GET['password']))
			{
				$password_user=md5($_GET['password']);//�ͻ�����������
				if($password_admin==$password_user) //���������ȷ
				{
					//��ʾ������Ϣ
					Codes_Show("Pass_file_name");
				}
				else
				{
					//��ʾ������Ϣ
					$info="<script>alert(\""."�������"."\")</script>";
					print $info;
					
				}
			}
		 ?>
		 
		 <?php
			function Codes_show($filename){
				print "pass_codes_info"; //��ע��Ϣ
				print "<pre class=\"brush:codes_show_type;\">\n";
				//���ļ��е������
				$codefile=substr($filename,0,strlen($filename)-4);
				$codefile.=".cod";
				$codefile="./save_code_doc/".$codefile;
				if(file_exists($codefile))
				{
					$codes=file($codefile);
					for($i=0;$i<count($codes);$i++)
						print $codes[$i];
				}
				else
					print "�����ļ������ڣ�";
				print "\n</pre>";
			}
		 ?>
		 
		 <?php
			function show_html($location){
				$password_admin=md5("default_password");
				$password_user=md5($_GET['password']);//�ͻ�����������
				if($password_admin==$password_user) //���������ȷ
				{
					//���������ȷ
					if($location=="input_password")
						print "none";
					else if($location=="body")
						print "style=\"background:url(img/bg.png) repeat;\"";
				}
				else
				{
					//����������
					if($location=="input_password")
						print "show";
					else if($location=="body")
						print "";
					
				}
			}
		 ?>
		 </div>
		 </center>
</body>
</html>