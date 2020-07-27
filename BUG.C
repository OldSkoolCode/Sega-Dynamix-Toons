/* * * * *
*
*  PHYSICS.C
*
*  This file contains routines to handle parts' physics.
*
*  By Kevin Ryan -- (c) 1992 Dynamix, Inc.
*
*  Modification History:
*  ---------------------
*  02/14/92 Kevin Ryan  File created
*
* * * * */

#include "vm.h"
#include "vm_mylib.h"
#include "tim.h"
#include "simlib.h"


void bounce(PART * cur_part)
{
   short slope,x,y,new_y,elast;
   long lx,ly;
   PART *col_part;
   COLLIDE_INFO *ci_ptr;
   P_PART_ELEMENTS elements1,elements2;

   ci_ptr = &cur_part->col_info;
   col_part = ci_ptr->part;
   elements1 = &prop[cur_part->type];
   elements2 = &prop[col_part->type];

   slope = ci_ptr->slope;
   if ((slope==0x0000) || (slope==(short)0x8000))
   {
      if (!ci_ptr->left_of_cog_supported)
         slope += 0x1000;
      else
         if (!ci_ptr->right_of_cog_supported)
            slope -= 0x1000;
   }

   x = cur_part->speed.x;
   y = cur_part->speed.y;
   rotate2d(&x,&y,slope);

   elast = min(elements1->elasticity,elements2->elasticity);

   if (elements1->friction != 0)
   {
      ly = smuls(y,elast);
      y = (short) (ly>>E_SHIFT);
      y = 0 - y;
      if (y < 0)
      {
         new_y = y + BOUNCE_DAMPER;
         if (new_y < 0)
            y = new_y;
         else
            y = 0;
      }
      else
      {
         new_y = y - BOUNCE_DAMPER;
         if (new_y > 0)
            y = new_y;
         else
            y = 0;
      }
   }
   else
      y = 0 - y;

   rotate2d(&x,&y,0-slope);

   cur_part->speed.x = x;
   cur_part->speed.y = y;

   check_term_velocity(cur_part);

   lx = (long) cur_part->scrn_loc.x;
   if (x>=0)
      cur_part->loc.x = ((lx+1)<<SCALE_SHIFT) - 1;
   else
      cur_part->loc.x = lx<<SCALE_SHIFT;

   ly = (long) cur_part->scrn_loc.y;
   if (elements1->acel >= 0)
      cur_part->loc.y = ((ly+1)<<SCALE_SHIFT) -1;
   else
      cur_part->loc.y = ly<<SCALE_SHIFT;
}

