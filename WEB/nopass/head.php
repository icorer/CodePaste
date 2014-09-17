<html>
	<head>
		<link rel="stylesheet" href="css/styles.css" media="screen">
		<link rel="stylesheet" type="text/css" href="list/css/normalize.css" />
		<link rel="stylesheet" type="text/css" href="list/css/demo.css" />
		<link rel="stylesheet" type="text/css" href="list/css/component.css" />
		<meta charset="GB2312" />
		<title>PagesTitle</title>
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
	
	<body style="margin:0px;background:url(img/bg.png) repeat;" >

<center>
	<script>alert("代码备注：codes_info")</script>

		 <?php
			function Codes_show($filename){
				//从文件中导入代码
				$codefile=$filename;
				if(file_exists($codefile))
				{
					$codes=file($codefile);
					for($i=0;$i<count($codes);$i++)
						print $codes[$i];
				}
				else
					print "代码文件不存在！";
			}
		 ?>
	
<div style="width:80%;height:100%;opacity:0.9;margin-top:5px;">
brushhead
<?php
Codes_Show("NoPass_file_name");
?>
</pre>
</div>
</center>
</html>