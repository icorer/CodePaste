<?php
	/*POST����ṹ
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
		
			//���ļ������в��ظ����� �����ļ�����
			$filename=time();
			$filename.=(string)mt_rand(0,99);
			//�ļ�ĩβû�к�׺�� �����������.html   ��������� .php ��̬����
			
			if($_POST['viewtype']=="public") //�����Դ���鿴
			{
				$filename.=".html";
				CreateDoc_NoPass($filename);
				if(file_exists("./save_code_doc/".$filename)) //����ļ��������������ļ���ַ
				{
					print $_POST['linkaddress']."/save_code_doc/".$filename;
				}
				else
					print "�������δ�ܳɹ�������룡\n�������ύ��";
			}
			else if($_POST['viewtype']=="private") //�����ʹ���鿴
			{
				$filename.=".php";
				CreateDoc_HavePass($filename);
				if(file_exists("./save_code_doc/".$filename)) //����ļ��������������ļ���ַ
				{
					print $_POST['linkaddress']."/save_code_doc/".$filename;
				}
				else
					print "�������δ�ܳɹ�������룡\n�������ύ��";
			}
		}
	}
?>


<?php
	//�������Ĵ���鿴���� �����ļ���nopass�ļ�����
	function CreateDoc_NoPass($filename){
			//����ͷ��
			$head=file("./nopass/head.php");
			//д�ļ�
			if(file_exists("./save_code_doc/".$filename)) //����ļ����� ������ͻ
			{
				print "�ļ���ͻ���������ύ��";
				exit();
			}
			$fp=fopen("./save_code_doc/".$filename,"w");
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("PagesTitle",$_POST['username']."�Ĵ���",$head[$i]);
				$head[$i]=str_replace("Pages_user_name",$_POST['username'],$head[$i]);
				$head[$i]=str_replace("codes_info",$_POST['info'],$head[$i]);
				fwrite($fp,$head[$i]);//���ͷ��
			}
				
			//�����ʽˢ
			fwrite($fp,"\n<pre class=\"brush:".$_POST['codestype'].";\">\n");
			//�������
			//��codes���д���
			$_POST['codes']=str_replace("<","&lt;",$_POST['codes']);//���÷���
			$_POST['codes']=str_replace("\\\"","\"",$_POST['codes']);//˫����
			$_POST['codes']=str_replace("\\\\","\\",$_POST['codes']); //��б��
			$_POST['codes']=str_replace("`","&",$_POST['codes']); //ָ�����
			$_POST['codes']=str_replace("\'","'",$_POST['codes']); //������
			fwrite($fp,$_POST['codes']);
			//�����β
			fwrite($fp,"</pre>");
			$foot=file('./nopass/foot.php');
			for($i=0;$i<count($foot);$i++)
				fwrite($fp,$foot[$i]);//���ͷ��
			fclose($fp);
		}
?>

<?php
	//��������Ĵ���鿴���� �����ļ���pass�ļ�����
	function CreateDoc_HavePass($filename){
		$head=file("./pass/moban.php");
		if(file_exists("./save_code_doc/".$filename)) //����ļ����� ������ͻ
		{
			print "�ļ���ͻ���������ύ��";
			exit();
		}
		$_POST['codes']=str_replace("<","&lt;",$_POST['codes']);
		$_POST['codes']=str_replace("`","&",$_POST['codes']);
		
		$fp=fopen("./save_code_doc/".$filename,"w");
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("pass_codes_pages_title",$_POST['username']."�Ĵ���",$head[$i]);
				$head[$i]=str_replace("pass_codes_info","<script>alert(\\\"".$_POST['info']."\\\")</script>",$head[$i]);
				$head[$i]=str_replace("show_codes_content",$_POST['codes'],$head[$i]);
				$head[$i]=str_replace("codes_show_type",$_POST['codestype'],$head[$i]);
				$head[$i]=str_replace("default_password",$_POST['password'],$head[$i]);
				fwrite($fp,$head[$i]);//���ͷ��
			}
		fclose($fp);
	}
?>

