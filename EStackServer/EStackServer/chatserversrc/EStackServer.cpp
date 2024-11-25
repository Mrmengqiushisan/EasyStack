// EStackServer.cpp: 定义应用程序的入口点。
//

#include "EStackServer.h"
#include <signal.h>
#include "net/EventLoop.h"
#include "IMServer.h"
#include "base/Singleton.h"
#include "MySqlManager.h" 
#include "UserManager.h"
#include <sys/socket.h>
#define LOG_INFO_IM(s) cout<<__FILE__<<": "<<__FUNCTION__<<"["<<__LINE__<<"]: "<<s<<endl
using namespace std;

void show_help(const char* cmd){
	cout<<"found error argument!\r\b";
	cout<<"usage: "<<endl;
	cout<<cmd<<" [-d]"<<endl;
	cout<<"\t-d run in daemon mode.\r\n";
}
void daemon(){
    signal(SIGCHLD,SIG_IGN);
    pid_t pid=fork();
    if(pid<0){
		cout<<"fork call error,code is "<<pid<<" error code is "<<errno<<endl;
        exit(-1);
    }
    if(pid>0)exit(0);
	//将子进程重新设计一个会话 避免父进程所在的会话结束时，把子进程带走
    setsid();
	//更改工作目录
	chdir("/home/wangtao/");
	//设置掩码
	umask(022);
	//关闭 重定向描述符
	int fd=open("/dev/null",O_RDWR);
	cout<<"evode success"<<endl;
	cout<<"fd is "<<fd<<endl;
	dup2(fd,STDIN_FILENO);
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);
	if(fd>STDERR_FILENO)close(fd);

}
void signal_exit(int signum){
	//TODO:退出的清除
	cout<<"signal "<<signum<<" found,exit..."<<endl;
	switch (signum){
	case SIGINT:
		break;
	case SIGKILL:
		break;
	case SIGTERM:
		break;
	case SIGILL:
		break;
	case SIGSEGV:
		break;
	case SIGABRT:
		break;
	default:
		break;
	}
	exit(signum);
}
void onConnection(const muduo::net::TcpConnectionPtr& conn){
	cout<<conn->name()<<endl;
}
void onMessage(const muduo::net::TcpConnectionPtr& coon,muduo::net::Buffer* buf,
muduo::Timestamp time){
	coon->send(buf);
}
int main(int argc, char* argv[], char* env[]){
	signal(SIGCHLD,	SIG_DFL);
	signal(SIGPIPE,	SIG_IGN);
	signal(SIGINT,	signal_exit);//Ctrl+C
	signal(SIGKILL,	signal_exit);
	signal(SIGTERM,	signal_exit);//进程结束信号
	signal(SIGILL,	signal_exit);//非法指令 产生core文件
	signal(SIGSEGV,	signal_exit);//段错误
	signal(SIGABRT,	signal_exit);//abort函数调用触发
	cout<<"imcharserver is opening ..."<<endl;
	int ch{ 0 };
	bool is_daemon=false;
	while ((ch = getopt(argc, argv, "ab:c::d")) != -1) {
		cout<<"ch= "<<(char)ch<<endl;
		cout << "current " << optind<<" value: "<<argv[optind-1]<<endl;
		switch (ch){
		case 'd':
			is_daemon=true;
			cout << "found d" << endl;
			break;
		default:
			show_help(argv[0]);   
			break;
		}
	}
	if(is_daemon){
		//TODO:开启守护进程
		daemon();
	}
	int num=1002;
	char* numch=(char*)&num;
	for(unsigned i=0;i<sizeof(int);i++){
		printf("%02X ",(unsigned)numch[i]&0xFF);
	}
	printf("\r\n");
	int bignum=htonl(num);
	char* bignumch=(char*)&bignum;
	for(unsigned i=0;i<sizeof(int);i++){
		printf("%02X ",(unsigned)bignumch[i]&0xFF);
	}
	printf("\r\n");
	//TODO:开启服务器逻辑
	muduo::net::EventLoop loop;
	if(!Singleton<MySqlManager>::instance().Init("127.0.0.1","root","521109xsq","myim")){
		cout<<"database init error!\r\n";
		return -2;
	}
	LOG_INFO_IM("mysql init success");
	if(!Singleton<UserManager>::instance().Init()){
		cout<<"load user failed!\r\n";
		return -3;
	}
	LOG_INFO_IM("mysql user init success");
	if(!Singleton<IMServer>::instance().Init("0.0.0.0",9527,&loop)){
		cout<<"server init error \r\n";
		return -1;
	}
	LOG_INFO_IM("imserver init success");
	loop.loop();
	cout<<"goodbye"<<endl;
	return 0;
}
