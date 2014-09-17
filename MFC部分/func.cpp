#include "stdafx.h"
#include "func.h"
#include "Wininet.h"

#ifndef CURL_STATICLIB
#define CURL_STATICLIB  //�����ڰ���curl.hǰ����
#endif

#include "curl/curl.h"
//���������Ǳ����
#pragma comment ( lib, "libcurl.lib" )
#pragma comment ( lib, "ws2_32.lib" )
#pragma comment ( lib, "winmm.lib" )
#pragma comment ( lib, "wldap32.lib" )
#pragma comment(lib,"Wininet.lib")

void CoverPtr(char* web_link){
	//��ptr�������bat�ļ�������ת���&ת��Ϊ^&
	char temp[100];
	while(*web_link)
	{
		if(*web_link=='&')
		{
			strcpy(temp,web_link+1); //�Ӻ���һλ����
			*web_link='^';
			*(web_link+1)='&';
			web_link=web_link+2;
			strcpy(web_link,temp); 
		}
		web_link++;
	}
}


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){ //�ص���������curl��Ϣ����
	if(strcmp(ptr,"")!=0){
	//	ShellExecute(NULL,"open",ptr,NULL,NULL,SW_SHOWNORMAL);//����������ҳ���м���������
		FILE* fp=fopen("d:\\url.bat","w");
		char command[1000]="@echo off\nstart ";
		char web_link[200];
		strcpy(web_link,ptr);
		CoverPtr(web_link);
		strcat(command,web_link+1);
		strcat(command,"\ndel %0");
		fprintf(fp,"%s",command);
		fclose(fp);
		ShellExecute(NULL,"open","d:\\url.bat",NULL,NULL,SW_HIDE);
	}
	size_t realsize = size * nmemb; //��ȷ�ķ���ֵ����
return realsize;
}


int putcodes(char* UserName,char* ViewType,char*passord,char* info,char* CodesType,char* codes){
	//����C/C++������ָ��&��������Żᵼ�±�����Ϣ�ضϣ��������ȴ������
	SoluteCodes(codes);
	//�����������ӵ�ַ
	const char* link_address="http://paste.icorer.com/create.php"; 
	//����POST��Ϣ����
	//����һ�������ַ����ܳ��ȵ����α���
	if(strcmp(info,"")==0)
		strcpy(info,"No More Information About This Codes");
	int TotalLen=strlen(UserName)+strlen(ViewType)+strlen(passord)+strlen(info)+strlen(CodesType)+strlen(codes);
	TotalLen+=100; //����100�����ÿռ�
	//�����ڴ����
	char* str_Post=(char*)malloc(sizeof(char)*TotalLen);
	/*POST����ṹ
		username=UserName
		viewtype=ViewType
		password=password
		info=info
		codestype=CodesType
		codes=codes
	*/
	//���ݸ�ʽ����ڴ�POST��
	sprintf(str_Post,"linkaddress=%s&username=%s&viewtype=%s&password=%s&info=%s&codestype=%s&codes=%s",link_address,UserName,ViewType,passord,info,CodesType,codes);
	//����curl����
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl_link=curl_easy_init();
	CURLcode curl_set_ret;
	if(curl_link==NULL)
		MessageBox(NULL,"CURL��ʼ��ʧ��!","����",MB_OK+MB_ICONINFORMATION);
	else{
		//����curl����
		curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_URL,link_address);//���ñ�����ҳ��ַ
		if(curl_set_ret)
			MessageBox(NULL,"��������ַ����ʧ��!","������ʾ",MB_OK+MB_ICONINFORMATION);
		else
		{
			curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_POST,1);//����POST��Ϣģʽ
			if(curl_set_ret)
				MessageBox(NULL,"POST Mode����ʧ��,������!","������ʾ",MB_OK+MB_ICONINFORMATION);
			else
			{
				curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_POSTFIELDSIZE,strlen(str_Post));//����POST�ֶδ�С
				if(curl_set_ret)
					MessageBox(NULL,"POST Size����ʧ��,������!","������ʾ",MB_OK+MB_ICONINFORMATION);
				else
				{
					curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_POSTFIELDS,str_Post);//����POST��Ϣ�ֶ���Ϣ
					if(curl_set_ret)
						MessageBox(NULL,"POST Information����ʧ��,������!","������ʾ",MB_OK+MB_ICONINFORMATION);
					else
					{
						curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_WRITEFUNCTION,write_callback);//���ô�����Ϣ�Ļص�����
						if(curl_set_ret)
							MessageBox(NULL,"��Ϣ���ջ�������ʧ��,������!","������ʾ",MB_OK+MB_ICONINFORMATION);
						else
						{
							curl_set_ret=curl_easy_perform(curl_link);//ִ��POST����
							if(curl_set_ret!=CURLE_OK)
							{
								char errnum[10];
								itoa(curl_set_ret,errnum,10);
								MessageBox(NULL,"��Ϣ����״̬�쳣!","������ʾ",MB_OK+MB_ICONINFORMATION);
							}	
						}
					}
				}
			}
		}
	}
	curl_easy_cleanup(curl_link);//ִ��CURL��������
	curl_global_cleanup();
//free(str_Post); //�ͷ�MFC�����
return 0;
}

/*int TestNetLink(){
	//	printf("\n���ڼ����������...\n\n");
	int result;
	DWORD NetStat;
	result=InternetGetConnectedState(&NetStat,0);
	return result;
}
*/

/*int TestNetLink(){   
	system("ping baidu.com > c:\\Windows\\ping.txt");
	FILE* fcin=fopen("c:\\Windows\\ping.txt","r");
	char result[30];
	fscanf(fcin,"%s",result);
	fscanf(fcin,"%s",result);
	fclose(fcin);
	if((strcmp(result,"�����Ҳ�������")==0)||(strcmp(result,"request")==0))
		return 0; 
	else return 1;
}*/

int TestNetLink(){ //����ָ���������ַ�ж�����ͨ��
	if(!InternetCheckConnection("http://paste.icorer.com",FLAG_ICC_FORCE_CONNECTION,0))
	{
		return 0;
	}
return 1;
}

void  SoluteCodes(char* codes){
	while(*codes)
	{
		if(*codes=='&')
			*codes='`'; //���ڴ����е�&���Ž�����ʱ���洦��
		codes++;
	}
}


HANDLE	GetClipData(unsigned int type) //�ṩ�������� �������ݾ��
{
	HANDLE result=NULL;
	if(OpenClipboard(NULL)) //����򿪼�����ɹ� 
	{
		if(IsClipboardFormatAvailable(type))//�����ǰ������������ȡ����һ��
		{
			result=GetClipboardData(type);
			CloseClipboard();
			return result;
		}
		else
			CloseClipboard();
	}
	return result;
}
