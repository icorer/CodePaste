<?php
	/*POST����ṹ
		linkaddress=�����������ļ��ĵ�ַ
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
					//print substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11)."/save_code_doc/".$filename;
					$show_link=substr($filename,0,strlen($filename)-5);//ȥ����ʽ��
					$show_server=substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11);
					print $show_server."/?link=".$show_link."&type=".$_POST['viewtype'];
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
					//print substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11)."/save_code_doc/".$filename;
					$show_link=substr($filename,0,strlen($filename)-4);//ȥ����ʽ��
					$show_server=substr($_POST['linkaddress'],0,strlen($_POST['linkaddress'])-11);
					print $show_server."/?link=".$show_link."&type=".$_POST['viewtype'];
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
			$codesfile="./save_code_doc/".substr($filename,0,strlen($filename)-5).".cod";
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("PagesTitle",$_POST['username']."�Ĵ���",$head[$i]);
				$head[$i]=str_replace("codes_info",$_POST['info'],$head[$i]);
				//�滻��ʽˢ
				$head[$i]=str_replace("brushhead","<pre class=\"brush:".$_POST['codestype'].";\">\n",$head[$i]);
				//�滻��ʾ���뺯���Ĳ���
				$head[$i]=str_replace("NoPass_file_name",$codesfile,$head[$i]);
				fwrite($fp,$head[$i]);//���ͷ��
			}
			//�Ѵ��뱣��������ļ��� .cod
			$fp_code=fopen($codesfile,"w");
			$_POST['codes']=str_replace("<","&lt;",$_POST['codes']);
			$_POST['codes']=str_replace("`","&",$_POST['codes']);
			fwrite($fp_code,$_POST['codes']);
			fclose($fp_code);
			//����������
			//�ر��ļ�ָ��
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
		//��POST��Ϣ�������ŵ�ת��,������ִ�����ʾ����,���ܷ������������в��죬����ע����һ����һ��
		//$_POST['codes']=addslashes($_POST['codes']);
		$_POST['info']=addslashes($_POST['info']); //��info��Ϣ��������ת��
		//$_POST['codes']=str_replace("\'","'",$_POST['codes']);
		$show_link=substr($filename,0,strlen($filename)-4);
		$fp=fopen("./save_code_doc/".$filename,"w");
			for($i=0;$i<count($head);$i++)
			{
				$head[$i]=str_replace("pass_codes_pages_title",$_POST['username']."�Ĵ���",$head[$i]);
				$head[$i]=str_replace("pass_codes_info","<script>alert(\\\""."���뱸ע:".$_POST['info']."\\\")</script>",$head[$i]);
				$head[$i]=str_replace("Pass_file_name",$filename,$head[$i]);
				$head[$i]=str_replace("codes_show_type",$_POST['codestype'],$head[$i]);
				$head[$i]=str_replace("default_password",$_POST['password'],$head[$i]);
				$head[$i]=str_replace("pass_file_link_number",$show_link,$head[$i]);
				fwrite($fp,$head[$i]);//���ͷ��
			}
		fclose($fp);
		//�Ѵ��뵥��д�����������ļ� cod�ļ�
 		$filename=substr($filename,0,strlen($filename)-4);
		$filename.=".cod";
		$fp=fopen("./save_code_doc/".$filename,"w+");
		fwrite($fp,$_POST['codes']);
		fclose($fp);
	}
?>

