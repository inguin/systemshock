/*

Copyright (C) 2015-2018 Night Dive Studios, LLC.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
*/
/*
 * $Source: n:/project/lib/src/3d/test/RCS/tmap.c $
 * $Revision: 1.1 $
 * $Author: kaboom $
 * $Date: 1993/07/28 21:04:37 $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

//#define __FAUXREND_SRC
#include "2d.h"
#include "3d.h"
#include "fauxrend.h"

#include "lg.h"

// prototypes
uchar fauxrend_start_frame(void);
void fauxrend_send_frame(void);
void setup_quad(fix x, fix y, fix z, int d, g3s_phandle *trans_p);
void test_3d(uchar *tmap, uchar* pal);
void checkKeyPress();

long fr_clear_color = 0xff;

fauxrend_context *_fr=NULL, *_sr;          /* current and default fauxrend contexts */
g3s_vector viewer_position;
g3s_angvec viewer_orientation;

#define _fr_top(vr) if (vr==NULL) _fr=_sr; else _fr=vr;
#define coor(val) (fix_make((eye[val]>>MAP_SH),(eye[val]&MAP_MK)<<MAP_MS))
#define ang(val)  (eye[val])

long gScreenRowbytes;
Ptr  gScreenAddress;

long eye[6] = {0,0,0,0,0,0};
long eye_scale[6]={1,1,1,128,128,128};
char eye_slew;

void eyepos_init(void)
{
   memset(eye,0,6*sizeof(long));
   eye_slew=1;
}

void eyepos_moveone(int which, int how)
{
   uchar cv[3]={0,2,1};
//   if (eye_slew)
   if (which>=3)                       /* angles */
      eye[which]+=how*eye_scale[which];
   else                                /* actual move */
   {
      g3s_vector v[3];
      g3_get_slew_step(how*fix_make(eye_scale[which],0),v+0,v+1,v+2);
//      mprintf("Note: v3 %x %x %x\n",v[2].x,v[2].y,v[2].z);
      if (which==2) how*=-1;
      eye[0]+=(fix_int(v[cv[which]].gX));
      eye[1]+=(fix_int(v[cv[which]].gZ));
      eye[2]-=(fix_int(v[cv[which]].gY));
   }
}

void eyepos_setone(int which, int val)
{
   eye[which]=val;
}

void fauxrend_set_context(fauxrend_context *frc)
{
   _sr=frc;
}

fauxrend_context *fauxrend_place_3d(fauxrend_context *fr, uchar db_buf, char axis, int fov, int xc, int yc, int wid, int hgt)
{
   if (fr==NULL)                         /* create new context */
      fr=(fauxrend_context *)malloc(sizeof(fauxrend_context));
   else gr_free_canvas(fr->draw_canvas); /* punt old canvas */
   fr->double_buffer=db_buf;
   if (db_buf)
   {
      fr->draw_canvas=gr_alloc_canvas(BMT_FLAT8,wid,hgt);
	   gr_set_canvas(fr->draw_canvas);
      gr_clear(fr_clear_color);
	   gr_set_canvas(grd_screen_canvas);
   }
   else
      fr->draw_canvas=gr_alloc_sub_canvas(grd_screen_canvas,xc,yc,wid,hgt);
   fr->xtop=xc; fr->ytop=yc;
   if (fov==0) fov=DEFAULT_FOV; if (axis==0) axis=DEFAULT_AXIS;
   fr->viewer_zoom=g3_get_zoom(axis,build_fix_angle(fov),wid,hgt);
   return fr;
}

uchar fauxrend_start_frame(void)
{
   gr_set_canvas(_fr->draw_canvas);
   viewer_position.gX = coor(EYE_X);
   viewer_position.gY =-coor(EYE_Z);
   viewer_position.gZ = coor(EYE_Y);
   viewer_orientation.pitch = ang(EYE_P);
   viewer_orientation.bank = ang(EYE_B);
   viewer_orientation.head = ang(EYE_H);
   g3_start_frame();
   g3_set_view_angles(&viewer_position,&viewer_orientation,ANGLE_ORDER,_fr->viewer_zoom);
   return TRUE;
}

void fauxrend_send_frame(void)
{
   g3_end_frame();
   gr_set_canvas(grd_screen_canvas);
   if (_fr->double_buffer) {
      gr_bitmap(&_fr->draw_canvas->bm,_fr->xtop,_fr->ytop);	
	   gr_set_canvas(_fr->draw_canvas);
      gr_clear(fr_clear_color);      /* should replace with generalized backdrop system */
	   gr_set_canvas(grd_screen_canvas);
   }
}


void setup_quad(fix x, fix y, fix z, int d, g3s_phandle *trans_p)
{
   g3s_vector cur_vec;

   cur_vec.xyz[0] = x;
   cur_vec.xyz[1] = y;
   cur_vec.xyz[2] = z;

   trans_p[0]=g3_transform_point(&cur_vec);
   cur_vec.xyz[0]+=fix_make(d,0);
   trans_p[1]=g3_transform_point(&cur_vec);
   cur_vec.xyz[1]+=fix_make(d,0);
   trans_p[2]=g3_transform_point(&cur_vec);
   cur_vec.xyz[0]-=fix_make(d,0);
   trans_p[3]=g3_transform_point(&cur_vec);
}

char byt_buf[64000];
char pal_buf[768];


int main(int argc, char *argv[])
{
   DebugString("Starting Test");

   if (argc != 3) {
      printf("usage: tmap bytfile, palfile\n");
      exit(1);
   }

   int fd = fopen(argv[1], "rb");
   fread(byt_buf, 1, 4096, fd);
   fclose(fd);

   fd = fopen(argv[2], "rb");
   fread(pal_buf, 1, 768, fd);
   fclose(fd);
}

void test_3d(uchar *tmap, uchar* pal)
{
   fauxrend_context *main_view;
   g3s_phandle trans[8];
   int c=0;
   int fd;
   grs_bitmap bm;
   g3s_vector du, dv;
   grs_screen *screen;
   
	BlockMove(tmap,byt_buf,4096);
	BlockMove(pal,pal_buf,768);

   gr_init();
   gr_set_mode(GRM_640x480x8, TRUE);
   screen = gr_alloc_screen(640,480);
   gr_set_screen (screen);
   g3_init(DEFAULT_PT_CNT,AXIS_ORDER);
   
   gr_set_fcolor(fr_clear_color);
   gr_init_bm(&bm, (uchar *) byt_buf, BMT_FLAT8, 0, 64, 64);
   main_view=fauxrend_place_3d(NULL,FALSE,0,0,0,0,640,480);
   fauxrend_set_context(main_view);

   while (1) {
      _fr_top(NULL);
      fauxrend_start_frame();
      setup_quad(-32768,-32768,4<<16,1,trans);
      g3_vec_sub(&du, &trans[1]->vec, &trans[0]->vec);
      g3_vec_sub(&dv, &trans[3]->vec, &trans[0]->vec);

      // Needs BlockMove
      //g3_draw_tmap_tile(trans[0], &du, &dv, 4, trans, &bm);

//    g3_draw_tmap_quad_tile (trans,&bm,1,1);

      fauxrend_send_frame();
      
      checkKeyPress();
      
      // Needs BlockMove
      //g3_draw_poly (0xff, 4, trans);
   }

	g3_shutdown();
   gr_close();
}

void checkKeyPress()
{
   /*
   c = 0;
   EventRecord  evt;
   if (GetNextEvent(keyDownMask+autoKeyMask,&evt)) c = evt.message & charCodeMask;
      switch (c) {
      case 'i': eyepos_moveone(EYE_Y,16); break;
      case 'j': eyepos_moveone(EYE_H,-16); break;
      case 'k': eyepos_moveone(EYE_Y,-16); break;
      case 'l': eyepos_moveone(EYE_H,16); break;
      case 'u': eyepos_moveone(EYE_Z,16); break;
      case 'o': eyepos_moveone(EYE_Z,-16); break;
      case '7': eyepos_moveone(EYE_X,16); break;
      case '9': eyepos_moveone(EYE_X,-16); break;
      case '8': eyepos_moveone(EYE_P,-16); break;
      case ',': eyepos_moveone(EYE_P,16); break;
      case 'm': eyepos_moveone(EYE_B,-16); break;
      case '.': eyepos_moveone(EYE_B,16); break;

      case 'I': eyepos_moveone(EYE_Y,4); break;
      case 'J': eyepos_moveone(EYE_H,-4); break;
      case 'K': eyepos_moveone(EYE_Y,-4); break;
      case 'L': eyepos_moveone(EYE_H,4); break;
      case 'U': eyepos_moveone(EYE_Z,4); break;
      case 'O': eyepos_moveone(EYE_Z,-4); break;
      case '&': eyepos_moveone(EYE_X,4); break;
      case '(': eyepos_moveone(EYE_X,-4); break;
      case '*': eyepos_moveone(EYE_P,-4); break;
      case '<': eyepos_moveone(EYE_P,4); break;
      case 'M': eyepos_moveone(EYE_B,-4); break;
      case '>': eyepos_moveone(EYE_B,4); break;

      default: break;
   }
   */
}
