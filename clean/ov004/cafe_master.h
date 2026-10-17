/* The cafe's master, drawn with the model npc_sp/model/pge: a special character's scene object
 * (main's special_scene_object.h) of vtable data_ov004_022546e0, 0x780 bytes, made by
 * func_ov004_02224c68, with its talk scene at 0x658. data_ov004_022580dc points to it from its
 * start (func_ov004_02224b30) until it may be deleted (func_ov004_02224b0c).
 *
 * The cafe's props (cafe_props.h) follow it through the functions here: the number of the
 * animation it plays (its animation player at 0x334), that animation's frame (its model's
 * frame at 0x190, 20.12) and two of its matrices, at 0x718 and 0x748. */
#ifndef CLEAN_OV004_CAFE_MASTER_H
#define CLEAN_OV004_CAFE_MASTER_H

#include "autoload_2/matrix.h"
#include "types.h"

u8 *CafeMaster_Destroy(u8 *master);
u8 *CafeMaster_Delete(u8 *master);
int CafeMaster_AnimNumber(void);
u16 CafeMaster_AnimFrame(void);
Mtx43 *CafeMaster_Matrix748(void);
Mtx43 *CafeMaster_Matrix718(void);

#endif
