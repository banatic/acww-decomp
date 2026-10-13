/* func_ov003_02222880 @ 0x02222880, 0x224 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Vec2;
typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int unk_00;
    int unk_04;
    u16 unk_08;
    u16 unk_0A;
    int unk_0C;
    int unk_10;
    int unk_14;
    char pad_18[0x24 - 0x18];
    int unk_24;
    int unk_28;
    int unk_2C;
    char pad_30[0x48 - 0x30];
    short unk_48;
    short unk_4A;
    short unk_4C;
    short unk_4E;
    short unk_50;
    short unk_52;
    int unk_54;
    int unk_58;
    int unk_5C;
    char pad_60[0xa0 - 0x60];
    u8 unk_A0;
    u8 unk_A1;
} UnkStruct_02222880;

extern int func_02045cec(int *, int);
typedef struct {
    char pad_00[10];
    u16 item;
    char tail[4];
} Entry;
extern Entry *func_02045bac(int);

extern void func_ov003_02222798(UnkStruct_02222880 *, Vec2 *, Vec3 *);
extern void func_ov003_022225c4(UnkStruct_02222880 *, Vec2 *, void *, int);
extern void func_ov003_02222560(UnkStruct_02222880 *, Vec2 *);
extern void func_ov003_0222250c(UnkStruct_02222880 *, Vec2 *, void *);
extern void func_ov003_02222360(UnkStruct_02222880 *, Vec2 *);
extern void func_ov003_0222228c(UnkStruct_02222880 *, Vec2 *, Vec3 *, int);
extern void func_ov003_0222214c(UnkStruct_02222880 *, Vec2 *, Vec3 *);
extern void func_ov003_022220a4(UnkStruct_02222880 *, Vec2 *, Vec3 *);
extern void func_ov003_02221f50(UnkStruct_02222880 *, Vec2 *, int);
extern void func_ov003_02221e78(UnkStruct_02222880 *, Vec2 *, Vec3 *, u16);
extern void func_ov003_02221da0(UnkStruct_02222880 *, Vec2 *);
extern void func_ov003_02221d3c(UnkStruct_02222880 *, Vec2 *);
extern void func_ov003_02221c80(UnkStruct_02222880 *, Vec3 *);
extern void func_ov003_02221a64(UnkStruct_02222880 *, Vec2 *, void *);

void func_ov003_02222880(UnkStruct_02222880 *self, int a1, Vec2 *pos, Vec3 *v, int sel, u16 a10, void *a11, short a12, int a13)
{
    int tmp[2];
    int r;

    self->unk_00 = a1;
    self->unk_04 = 1;
    self->unk_0C = sel;
    self->unk_10 = pos->x;
    self->unk_14 = pos->y;
    self->unk_48 = a12;
    self->unk_4A = 0;
    self->unk_54 = v->x;
    self->unk_58 = v->y;
    self->unk_5C = v->z;
    self->unk_A0 = 1;
    self->unk_A1 = 0;
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_2C = 0;

    tmp[0] = self->unk_10;
    tmp[1] = self->unk_14;
    r = func_02045cec(tmp, 0);
    if (r >= 0) {
        self->unk_0A = func_02045bac(r)->item;
    } else {
        self->unk_0A = 0xfff1;
    }

    self->unk_08 = a10;
    self->unk_4C = 0;
    self->unk_4E = 0;
    self->unk_50 = 0;
    self->unk_52 = 0x1f;

    switch (sel) {
        case 0:
        case 13: {
            Vec3 t3;
            Vec2 t2;
            t3.x = v->x;
            t3.y = v->y;
            t3.z = v->z;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02222798(self, &t2, &t3);
            break;
        }
        case 1: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_022225c4(self, &t2, a11, a13);
            break;
        }
        case 2: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02222560(self, &t2);
            break;
        }
        case 3: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_0222250c(self, &t2, a11);
            break;
        }
        case 4: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02222360(self, &t2);
            break;
        }
        case 5: {
            Vec3 t3;
            Vec2 t2;
            t3.x = v->x;
            t3.y = v->y;
            t3.z = v->z;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_0222228c(self, &t2, &t3, a13);
            break;
        }
        case 6: {
            Vec3 t3;
            Vec2 t2;
            t3.x = v->x;
            t3.y = v->y;
            t3.z = v->z;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_0222214c(self, &t2, &t3);
            break;
        }
        case 7: {
            Vec3 t3;
            Vec2 t2;
            t3.x = v->x;
            t3.y = v->y;
            t3.z = v->z;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_022220a4(self, &t2, &t3);
            break;
        }
        case 8: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02221f50(self, &t2, a12);
            break;
        }
        case 9: {
            Vec3 t3;
            Vec2 t2;
            t3.x = v->x;
            t3.y = v->y;
            t3.z = v->z;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02221e78(self, &t2, &t3, a10);
            break;
        }
        case 10: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02221da0(self, &t2);
            break;
        }
        case 11: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02221d3c(self, &t2);
            break;
        }
        case 12: {
            Vec3 t3;
            t3.x = v->x;
            t3.y = v->y;
            t3.z = v->z;
            func_ov003_02221c80(self, &t3);
            break;
        }
        case 14: {
            Vec2 t2;
            t2.x = pos->x;
            t2.y = pos->y;
            func_ov003_02221a64(self, &t2, a11);
            break;
        }
    }
}
