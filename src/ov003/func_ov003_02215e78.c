/* func_ov003_02215e78 @ 0x02215e78, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} Vec;

extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern void func_02060438(void *, Vec *);
extern void func_ov003_02215ef8(void *, fx32, fx32);
extern int func_020e8ed8(fx32, fx32);

typedef struct {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x76c];
    short unk_7D4;
} UnkStruct_02215e78;
typedef struct {
    fx32 x;
    fx32 z;
} UnkStruct_02215e78_2;

void func_ov003_02215e78(UnkStruct_02215e78 *self, void *data, int previous)
{
    Vec v[2];
    UnkStruct_02215e78_2 *p;
    fx32 x, z;
    func_020109a0(self, 0x52, 3, 0);
    func_0205eae0((char *) self + 0x5a0, 0x15, 3, 0);
    p = (UnkStruct_02215e78_2 *) ((char *) data + 0xc);
    z = p->z;
    x = p->x;
    v[0].x = x;
    v[0].y = 0;
    v[0].z = z;
    v[1].x = x;
    v[1].y = 0;
    v[1].z = z;
    func_02060438((char *) self + 0x5c8, &v[1]);
    func_ov003_02215ef8((char *) self + 0x8f0, v[0].x, v[0].z);
    self->unk_7D4 = (short) func_020e8ed8(v[0].x - self->pos.x, v[0].z - self->pos.z);
}
