/*
IMPORTANT : this program is not finished and will be finished later !!!!

*/
#include <X11/Xlib.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <sys/mman.h> 
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 8192
#define READING_SIZE 2048
#define BUFFER_SIZE 8192


struct mountinfo{
	char dev[32];
	char path[32];
	char format[8];

	};

struct DiskElement{
struct mountinfo mi;
unsigned long total;
unsigned long free;

};

struct X11diskusage{

struct DiskElement **disk;
//int fd;
int disk_count;

Display* display;
Window window;
GC gc;


};


void render(struct X11diskusage *x11du){
int k; 
XSetForeground(x11du->display, x11du->gc, 0xffffff);
 XWindowAttributes attrs;
XGetWindowAttributes(x11du->display, x11du->window, &attrs);
XFillRectangle(x11du->display, x11du->window, x11du->gc, 0, 0, attrs.width, attrs.height);



}




int main(int argc, char* argv[]){

Display* display = XOpenDisplay(NULL);
    XEvent event;
	GC gc;
	struct X11diskusage *x11du = malloc(sizeof(struct X11diskusage));
	int screen = DefaultScreen(display); int k;
	   Window window = XCreateSimpleWindow(
        display, XDefaultRootWindow(display),
        100, 100, 400, 400, 4, 0xff0000, WhitePixel(display, screen));

		 XMapWindow(display, window);
    XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask | ButtonMotionMask);	
   XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask | ButtonMotionMask);
	gc=XCreateGC(display, window, 0,0);
		x11du->window = window; x11du->display=display; x11du->gc=gc;

	x11du->disk = malloc(sizeof(struct DiskElement*) * ( 40));
	x11du->disk_count = 0;
	for(k=0;k<40;k++){x11du->disk[k] = malloc(sizeof(struct DiskElement)); 


int fd;
   char *buf;


	 buf = (char*) syscall(SYS_mmap,0,  BUF_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

 fd = open("/proc/mounts", O_RDONLY );

  enum MState{ReadingDevice,ReadingMountPoint,ReadingFormat,ReadingOtherData};	
  enum MState state=ReadingDevice;

 char buffer[2048];
	int read_byte, offset=0 ;

  

	 struct mountinfo mi;
	 int l=0;

  while( (read_byte = read(fd,buffer + offset,
                         (BUFFER_SIZE-offset)  >= READING_SIZE ? READING_SIZE :  (BUFFER_SIZE-offset)   )) >0 ) 
    for(k=offset;k<read_byte + offset;k++) {

	switch(state){

		case ReadingDevice : if(buffer[k]!=' ') mi.dev[l++]=buffer[k];else { mi.dev[l]='\0'; state=ReadingMountPoint; l=0;}  break;
		case ReadingMountPoint : if(buffer[k]!=' ') mi.path[l++]=buffer[k];else { mi.path[l]='\0'; state=ReadingFormat; l=0;}  break;
		case ReadingFormat : if(buffer[k]!=' ') mi.format[l++]=buffer[k];else { mi.format[l]='\0'; state=ReadingOtherData; l=0;}  break;
		case ReadingOtherData : if(buffer[k] == '\n') {
					
			int dfd = open(mi.path, O_RDONLY | O_DIRECTORY);
			char *stat_buffer = (char*) syscall(SYS_mmap,0,  BUF_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
			fstatfs(dfd,stat_buffer);
			
			unsigned long  xtotal =  (*(unsigned long *)(stat_buffer+16)) * (*(unsigned long *)(stat_buffer+8));
			unsigned long  xfree =   (*(unsigned long *)(stat_buffer+32)) * (*(unsigned long *)(stat_buffer+8));
			

			x11du->disk[x11du->disk_count]->mi=mi;
			x11du->disk[x11du->disk_count]->total=xtotal;	
			x11du->disk[x11du->disk_count++]->free=xfree;	
			state=ReadingDevice;
					}break;

		}


}

	while (True) {
	XNextEvent(display, &event);
	switch(event.type){

	render(x11du);



	}


		}
 

 }

}
