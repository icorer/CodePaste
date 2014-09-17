#include "stdafx.h"
#include "func.h"
#include "Wininet.h"

#ifndef CURL_STATICLIB
#define CURL_STATICLIB  //必须在包含curl.h前定义
#endif

#include "curl/curl.h"
//以下四项是必须的
#pragma comment ( lib, "libcurl.lib" )
#pragma comment ( lib, "ws2_32.lib" )
#pragma comment ( lib, "winmm.lib" )
#pragma comment ( lib, "wldap32.lib" )
#pragma comment(lib,"Wininet.lib")

void CoverPtr(char* web_link){
	//对ptr进行针对bat文件的命令转义把&转义为^&
	char temp[100];
	while(*web_link)
	{
		if(*web_link=='&')
		{
			strcpy(temp,web_link+1); //从后面一位拷贝
			*web_link='^';
			*(web_link+1)='&';
			web_link=web_link+2;
			strcpy(web_link,temp); 
		}
		web_link++;
	}
}


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){ //回调函数进行curl信息处理
	if(strcmp(ptr,"")!=0){
	//	ShellExecute(NULL,"open",ptr,NULL,NULL,SW_SHOWNORMAL);//这种运行网页带有兼容性问题
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
	size_t realsize = size * nmemb; //正确的返回值设置
return realsize;
}


int putcodes(char* UserName,char* ViewType,char*passord,char* info,char* CodesType,char* codes){
	//由于C/C++语言有指针&，这个符号会导致报表信息截断，我们首先处理代码
	SoluteCodes(codes);
	//定义网络连接地址
	const char* link_address="http://paste.icorer.com/create.php"; 
	//进行POST信息整合
	//定义一个计算字符串总长度的整形变量
	if(strcmp(info,"")==0)
		strcpy(info,"No More Information About This Codes");
	int TotalLen=strlen(UserName)+strlen(ViewType)+strlen(passord)+strlen(info)+strlen(CodesType)+strlen(codes);
	TotalLen+=100; //加上100个备用空间
	//进行内存分配
	char* str_Post=(char*)malloc(sizeof(char)*TotalLen);
	/*POST报表结构
		username=UserName
		viewtype=ViewType
		password=password
		info=info
		codestype=CodesType
		codes=codes
	*/
	//根据格式填充内存POST表
	sprintf(str_Post,"linkaddress=%s&username=%s&viewtype=%s&password=%s&info=%s&codestype=%s&codes=%s",link_address,UserName,ViewType,passord,info,CodesType,codes);
	//进行curl操作
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl_link=curl_easy_init();
	CURLcode curl_set_ret;
	if(curl_link==NULL)
		MessageBox(NULL,"CURL初始化失败!","错误",MB_OK+MB_ICONINFORMATION);
	else{
		//进行curl设置
		curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_URL,link_address);//设置报表网页地址
		if(curl_set_ret)
			MessageBox(NULL,"服务器地址连接失败!","操作提示",MB_OK+MB_ICONINFORMATION);
		else
		{
			curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_POST,1);//开启POST信息模式
			if(curl_set_ret)
				MessageBox(NULL,"POST Mode设置失败,请重试!","操作提示",MB_OK+MB_ICONINFORMATION);
			else
			{
				curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_POSTFIELDSIZE,strlen(str_Post));//设置POST字段大小
				if(curl_set_ret)
					MessageBox(NULL,"POST Size设置失败,请重试!","操作提示",MB_OK+MB_ICONINFORMATION);
				else
				{
					curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_POSTFIELDS,str_Post);//设置POST信息字段信息
					if(curl_set_ret)
						MessageBox(NULL,"POST Information设置失败,请重试!","操作提示",MB_OK+MB_ICONINFORMATION);
					else
					{
						curl_set_ret=curl_easy_setopt(curl_link,CURLOPT_WRITEFUNCTION,write_callback);//设置处理信息的回调函数
						if(curl_set_ret)
							MessageBox(NULL,"信息接收环境设置失败,请重试!","操作提示",MB_OK+MB_ICONINFORMATION);
						else
						{
							curl_set_ret=curl_easy_perform(curl_link);//执行POST发送
							if(curl_set_ret!=CURLE_OK)
							{
								char errnum[10];
								itoa(curl_set_ret,errnum,10);
								MessageBox(NULL,"信息处理状态异常!","操作提示",MB_OK+MB_ICONINFORMATION);
							}	
						}
					}
				}
			}
		}
	}
	curl_easy_cleanup(curl_link);//执行CURL的清理工作
	curl_global_cleanup();
//free(str_Post); //释放MFC会出错
return 0;
}

/*int TestNetLink(){
	//	printf("\n正在检测网络配置...\n\n");
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
	if((strcmp(result,"请求找不到主机")==0)||(strcmp(result,"request")==0))
		return 0; 
	else return 1;
}*/

int TestNetLink(){ //根据指定的网络地址判断链接通断
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
			*codes='`'; //对于代码中的&符号进行暂时代替处理
		codes++;
	}
}


HANDLE	GetClipData(unsigned int type) //提供数据类型 返回内容句柄
{
	HANDLE result=NULL;
	if(OpenClipboard(NULL)) //如果打开剪贴板成功 
	{
		if(IsClipboardFormatAvailable(type))//如果当前数据类型与索取类型一样
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
