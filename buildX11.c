#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
/*
A helper program which allow to compile X11 apps 
so you don't need to explicitly indicate the X11 library paths everytime you compile your X11 code

NOTE : In my case the X11 libraries are located at : "/home/user/X11" 
 But, you have to change this path accordingly before compiling the code
 
*/

int main(int argc,char * argv[]) {

pid_t gccx11_pid ;

char * argvx11[240 ] =  {"gcc","-I","/home/user/X11/libx11-dev_2%3a1.6.4-3ubuntu0.4_amd64/data/usr/include","-w","-L","/home/user/X11/libx11-dev_2%3a1.6.4-3ubuntu0.4_amd64/data/usr/lib/x86_64-linux-gnu/","-L","x11-xcb1/usr/lib/x86_64-linux-gnu/","-L","/home/user/X11/x11-xau/usr/lib/x86_64-linux-gnu","-L","/home/user/X11/x11-xdmcp/usr/lib/x86_64-linux-gnu"} ; 
int k ;




for(k=1;k<=argc;k++) argvx11[k+11] = argv[k]; 


argvx11[k+10] = "-lX11";
argvx11[k+11] = "-lxcb";
argvx11[k+12] = "-lXau";
argvx11[k+13] = "-lXdmcp";
argvx11[k+14] = NULL;

if((gccx11_pid = vfork()) == 0)
execvp("gcc",argvx11) ; 

waitpid(gccx11_pid,NULL,0);


}
