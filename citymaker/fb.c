/*
 * fb.c - Drawing things on the framebuffer
 * Copyright (C) 2015 Paolo Niccolò Giubelli <paoloniccolo.giubelli@gmail.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <errno.h>
#include "fb.h"
#include "city.h"

void hide_cursor()
{
	printf("\e[?25l");
}
void show_cursor()
{
	printf("\e[?25h");
}
void clear_fb(struct fbdev* fb)
{
	char *ptr;
	ptr = fb->fbmem;

	memset(ptr,0,fb->finfo.line_length*fb->vinfo.yres);
	printf(">>>%d\n", fb->vinfo);
	/*
	 * DEBUGGING STUFF	
	printf("xres:yres:depth=%d:%d:%d\n",fb->vinfo.xres,fb->vinfo.yres,fb->vinfo.bits_per_pixel);
	printf("smemstart:%lu\n",fb->finfo.smem_start);
	printf("smemlen:%lu\n",fb->finfo.smem_len);
	printf("xpanstep,ypanstep:%d,%d\n",fb->finfo.xpanstep,fb->finfo.ypanstep);
	printf("LL:%d\n",fb->finfo.line_length);
	printf("Margins (L,R): (%d,%d)\n",fb->vinfo.left_margin,fb->vinfo.right_margin);
	printf("mmio length: %d\n",fb->finfo.mmio_len);
	printf("hsync,vsync: %d,%d\n",fb->vinfo.hsync_len,fb->vinfo.vsync_len);
	printf("Standard? %d\n",fb->vinfo.nonstd);
	int ii;
	for(ii=0;ii<768;ii++){
		if(ii%2==0){
			memset(ptr+ii*fb->finfo.line_length, 101, 4*1366);
		}
	}
	*/

	//memset(fb->fbmem+fb->w*fb->d*2,255,fb->w*fb->d);
	//memset(&(fb->fbmem[fb->w*fb->h*fb->d-fb->d]), 255, fb->d);
	//
}
struct fbdev* init_fb()
{	
	int fd = open(FB_DEV,O_RDWR);
	if(fd<0){
		printf("Errore nell'aprire il framebuffer\n");
		abort();
	}
	struct fbdev* fb = (struct fbdev*)xmalloc(sizeof(struct fbdev));
	if(ioctl(fd,FBIOGET_FSCREENINFO,&(fb->finfo))){
		printf("Errore A %d\n", errno);
		abort();
	}
	if(ioctl(fd,FBIOGET_VSCREENINFO,&(fb->vinfo))){
		printf("Errore B %d\n", errno);
		abort();
	}
	fb->screensize = fb->vinfo.xres*fb->vinfo.yres*fb->vinfo.bits_per_pixel/8;
	fb->fbmem = (struct px*)mmap(NULL,fb->finfo.smem_len,PROT_READ|PROT_WRITE,
				MAP_SHARED,fd,0);
	close(fd);
	clear_fb(fb);
	return fb;
}
void draw_square(struct fbdev* fb, struct coords_s origin, 
		unsigned short size){
	int ii;	
	for(ii=origin.y*FB_SCALE;ii<(origin.y+size)*FB_SCALE;ii++){
		memset(fb->fbmem+ii*fb->finfo.line_length+origin.x*FB_SCALE,
				200,4*size*FB_SCALE);

	}	
}
void draw_building(struct fbdev*fb, struct building* b)
{
	draw_square(fb, b->origin, b->side_size);
}
void draw_city(struct fbdev* dev,struct city* the_city){
	hide_cursor();
	struct city_buildings* a_b = the_city->all_buildings;
	while(a_b!=NULL){
		struct building *b = a_b->building;
		draw_building(dev, b);
		a_b = a_b->next;
	}
	int t;
	scanf("%d",&t);
	show_cursor();
}
