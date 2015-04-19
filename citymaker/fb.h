#ifndef FB_H
#include <inttypes.h>
#include <linux/fb.h>
#define FB_DEV "/dev/fb0"
#define FB_SCALE 5

struct px{
	uint8_t r,g,b,a;
};
struct fbdev {
	char* fbmem;
	struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
	long int screensize;
	unsigned short w,h,d;
};
void hide_cursor();
void show_cursor();
struct fbdev* init_fb();
#define FB_H
#endif
