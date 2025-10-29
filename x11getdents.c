/*
IMPORTANT : This code is incomplete and will be completed later !

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
#define MAX_COUNT 40

struct DirElement {
char *name;
Window *win;
char d_type;
int x;
int y;


};

struct X11getdents{

struct DirElement **dir;
int fd;
int dir_count;

Display* display;
Window window;
GC gc;


};

void list(struct X11getdents* x11gt,int fd){

 x11gt->fd = fd;
 int nread;
   char *buf;
   void *d;
    int bpos;	
   char d_type;
   int position;
 int k;
	x11gt->dir_count=0;
	//int dir_index=0; 


  buf = (char*) syscall(SYS_mmap,0,  BUF_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

			while ((nread = syscall(SYS_getdents64, x11gt->fd, buf, BUF_SIZE))>0 )  for (bpos = 0; bpos < nread && x11gt->dir_count < MAX_COUNT;bpos +=*((unsigned short *) (d +16) )) {

		d =  (buf + bpos);
		d_type = *(buf + bpos +18);
		const char *name = ((char *) (d +19) );
		int size = strlen(name);
		printf("%s %lx\n",name,x11gt->dir[x11gt->dir_count]->name); 
		strcpy(x11gt->dir[x11gt->dir_count]->name,name);
		x11gt->dir[x11gt->dir_count]->d_type = d_type;


		x11gt->dir_count++;
		}


}

void render(struct X11getdents* x11gt){
 int k; 
 for(k=0;k<x11gt->dir_count;k++)   {
	if(x11gt->dir[k]->d_type == 4)XSetForeground(x11gt->display, x11gt->gc, 0xf2f542);else XSetForeground(x11gt->display, x11gt->gc, 0xf1f1f1);
	XFillRectangle(x11gt->display, x11gt->window, x11gt->gc, x11gt->dir[k]->x, x11gt->dir[k]->y - 10, 300, 15);

		XSetForeground(x11gt->display, x11gt->gc, 0x000000);
  XDrawString(x11gt->display, x11gt->window, x11gt->gc, x11gt->dir[k]->x, x11gt->dir[k]->y, x11gt->dir[k]->name, strlen(x11gt->dir[k]->name));
		
	
	}


}

int main(int argc, char* argv[])
{
    Display* display = XOpenDisplay(NULL);
    XEvent event;
	GC gc;
	struct X11getdents *x11gt = malloc(sizeof(struct X11getdents));
	int screen = DefaultScreen(display); int k;
	   Window window = XCreateSimpleWindow(
        display, XDefaultRootWindow(display),
        100, 100, 400, 400, 4, 0xff0000, WhitePixel(display, screen));


	
	 XMapWindow(display, window);
    XSelectInput(display, window, KeyPressMask | ButtonPressMask | ExposureMask | ButtonMotionMask);	
	gc=XCreateGC(display, window, 0,0);
		x11gt->window = window; x11gt->display=display; x11gt->gc=gc;

	x11gt->dir = malloc(sizeof(struct DirElement*) * (x11gt->dir_count = 40));
	
	for(k=0;k<x11gt->dir_count;k++){x11gt->dir[k] = malloc(sizeof(struct DirElement)); 
	x11gt->dir[k]->x=20;
	x11gt->dir[k]->y=20*k+40;
	char buffer[20];
	x11gt->dir[k]->name=malloc(40);

	}
	list(x11gt,open(".", O_RDONLY | O_DIRECTORY));
	while (True) {
	XNextEvent(display, &event);
	switch(event.type) {
	case ButtonPress :  ;



			}



	render(x11gt);
	}





}
