<?php
	/*POST报表结构
		username=UserName
		viewtype=ViewType
		password=password
		info=info
		codestype=CodesType
		codes=codes
	*/
?>

<?php
	if(isset($_POST['username']))
	{
		if($_POST['codes']){
		
			//对文件名进行不重复处理 构造文件名称
			$filename=time();
			$filename.=(string)mt_rand(0,99);
			//文件末尾没有后缀名 如果无密码则.html   如果有密码 .php 动态处理
			
			if($_POST['viewtype']=="public") //公开性代码查看
			{
				$filename.=".html";
				CreateDoc_NoPass($filename);
				if(file_exists("./save_code_doc/".$filename)) //如果文件存在则反馈网络文件地址
				{
					print $_POST['linkaddress']."/save_code_doc/".$filename;
				}
				else
					print "网络错误，未能成功保存代码！\n请重新提交。";
			}
			else if($_POST['viewtype']=="private") //密码型代码查看
			{
				$filename.=".php";
				CreateDoc_HavePass($filename);
				if(file_exists("./save_code_doc/".$filename)) //如果文件存在则反馈网络文件地址
				{
					print $_POST['linkaddress']."/save_code_doc/".$filename;
				}
				else
					print "网络错误，未能成功保存代码！\n请重新提交。";
			}
		}
	}
?>


<?php
	//无密码版的代码查看函数 引用文件在nopass文件夹中
	function CreateDoc_NoPass($filename){
			//读入头部
			$head=file("./nopass/head.php");
			//写文件
			if(file_exists("./save_code_doc/".$filename)) //如果文件存在 发生冲突
			{
				print "文件冲突，请重新提交！";
				exit();
			}
			$fp=fopen("./save_code_doc/".$filename,"w");
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("PagesTitle",$_POST['username']."的代码",$head[$i]);
				$head[$i]=str_replace("Pages_user_name",$_POST['username'],$head[$i]);
				$head[$i]=str_replace("codes_info",$_POST['info'],$head[$i]);
				fwrite($fp,$head[$i]);//输出头部
			}
				
			//输出格式刷
			fwrite($fp,"\n<pre class=\"brush:".$_POST['codestype'].";\">\n");
			//输出代码
			//对codes进行处理
			$_POST['codes']=str_replace("<","&lt;",$_POST['codes']);//引用符号
			$_POST['codes']=str_replace("\\\"","\"",$_POST['codes']);//双引号
			$_POST['codes']=str_replace("\\\\","\\",$_POST['codes']); //单斜线
			$_POST['codes']=str_replace("`","&",$_POST['codes']); //指针符号
			$_POST['codes']=str_replace("\'","'",$_POST['codes']); //单引号
			fwrite($fp,$_POST['codes']);
			//输出结尾
			fwrite($fp,"</pre>");
			$foot=file('./nopass/foot.php');
			for($i=0;$i<count($foot);$i++)
				fwrite($fp,$foot[$i]);//输出头部
			fclose($fp);
		}
?>

<?php
	//含有密码的代码查看函数 引用文件在pass文件夹中
	function CreateDoc_HavePass($filename){
		$head=file("./pass/moban.php");
		if(file_exists("./save_code_doc/".$filename)) //如果文件存在 发生冲突
		{
			print "文件冲突，请重新提交！";
			exit();
		}
		$_POST['codes']=str_replace("<","&lt;",$_POST['codes']);
		$_POST['codes']=str_replace("`","&",$_POST['codes']);
		
		$fp=fopen("./save_code_doc/".$filename,"w");
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("pass_codes_pages_title",$_POST['username']."的代码",$head[$i]);
				$head[$i]=str_replace("pass_codes_info","<script>alert(\\\"".$_POST['info']."\\\")</script>",$head[$i]);
				$head[$i]=str_replace("show_codes_content",$_POST['codes'],$head[$i]);
				$head[$i]=str_replace("codes_show_type",$_POST['codestype'],$head[$i]);
				$head[$i]=str_replace("default_password",$_POST['password'],$head[$i]);
				fwrite($fp,$head[$i]);//输出头部
			}
		fclose($fp);
	}
?>

