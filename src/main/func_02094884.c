/* func_02094884 @ 0x02094884, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: storing each triple's first member through self and the rest through a member pointer gives the base-register stores; plain field stores and a struct copy change the size */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} UnkStruct_02094884_2;
typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Mid;
typedef struct {
    u16 p;
    u16 q;
    u16 r;
} Tail;
typedef struct {
    u32 head;
    UnkStruct_02094884_2 inner;
    Mid mid;
    Tail tail;
} UnkStruct_02094884;
extern u32 data_021d5658[3];
void func_02094884(UnkStruct_02094884 *self)
{
    u32 *ptr;
    ptr = data_021d5658;
    {
        UnkStruct_02094884_2 *ip = &self->inner;
        if (ptr) {
            self->inner.a = ptr[0];
            ip->b = ptr[1];
            ip->c = ptr[2];
        } else {
            self->inner.a = data_021d5658[0];
            ip->b = data_021d5658[1];
            ip->c = data_021d5658[2];
        }
    }
    {
        Mid *mp = &self->mid;
        self->mid.x = 0x1000;
        mp->y = 0x1000;
        mp->z = 0x1000;
    }
    {
        Tail *tp = &self->tail;
        self->tail.p = 0;
        tp->q = 0;
        tp->r = 0;
    }
}
