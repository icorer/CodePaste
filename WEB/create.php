<?php
	/*POST报表结构
		linkaddress=服务器创建文件的地址
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
					//print substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11)."/save_code_doc/".$filename;
					$show_link=substr($filename,0,strlen($filename)-5);//去除格式名
					$show_server=substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11);
					print $show_server."/?link=".$show_link."&type=".$_POST['viewtype'];
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
					//print substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11)."/save_code_doc/".$filename;
					$show_link=substr($filename,0,strlen($filename)-4);//去除格式名
					$show_server=substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11);
					print $show_server."/?link=".$show_link."&type=".$_POST['viewtype'];
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
			$codesfile="./save_code_doc/".substr($filename,0,strlen($filename)-5).".cod";
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("PagesTitle",$_POST['username']."的代码",$head[$i]);
				$head[$i]=str_replace("codes_info",$_POST['info'],$head[$i]);
				//替换格式刷
				$head[$i]=str_replace("brushhead","<pre class=\"brush:".$_POST['codestype'].";\">\n",$head[$i]);
				//替换显示代码函数的参数
				$head[$i]=str_replace("NoPass_file_name",$codesfile,$head[$i]);
				fwrite($fp,$head[$i]);//输出头部
			}
			//把代码保存进代码文件中 .cod
			$fp_code=fopen($codesfile,"w");
			$_POST['codes']=str_replace("<","&lt;",$_POST['codes']);
			$_POST['codes']=str_replace("`","&",$_POST['codes']);
			fwrite($fp_code,$_POST['codes']);
			fclose($fp_code);
			//保存代码结束
			//关闭文件指针
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
		//对POST信息进行引号的转义,如果发现代码显示异样,可能服务器的设置有差异，可以注释下一行试一试
		//$_POST['codes']=addslashes($_POST['codes']);
		$_POST['info']=addslashes($_POST['info']); //对info信息进行引号转义
		//$_POST['codes']=str_replace("\'","'",$_POST['codes']);
		$show_link=substr($filename,0,strlen($filename)-4);
		$fp=fopen("./save_code_doc/".$filename,"w");
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("pass_codes_pages_title",$_POST['username']."的代码",$head[$i]);
				$head[$i]=str_replace("pass_codes_info","<script>alert(\\\""."代码备注:".$_POST['info']."\\\")</script>",$head[$i]);
				$head[$i]=str_replace("Pass_file_name",$filename,$head[$i]);
				$head[$i]=str_replace("codes_show_type",$_POST['codestype'],$head[$i]);
				$head[$i]=str_replace("default_password",$_POST['password'],$head[$i]);
				$head[$i]=str_replace("pass_file_link_number",$show_link,$head[$i]);
				fwrite($fp,$head[$i]);//输出头部
			}
		fclose($fp);
		//把代码单独写进单独代码文件 cod文件
 		$filename=substr($filename,0,strlen($filename)-4);
		$filename.=".cod";
		$fp=fopen("./save_code_doc/".$filename,"w+");
		fwrite($fp,$_POST['codes']);
		fclose($fp);
	}
?>

