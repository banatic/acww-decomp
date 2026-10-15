/* func_020c1fc8 @ 0x020c1fc8, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016884(void *a, int b, void *c);
extern int func_020912d4(int id, void *p1, void *p2, int flag);
extern int func_02019de8(void *p);
extern int func_02019c20(void *p, int a, int b, int c, unsigned short d, int e);
extern void func_020c26b4(void *p, int flag);
extern unsigned short data_020c80f8;

typedef struct Vec3 {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_020c1fc8 {
    unsigned char pad_00[0x5c];           // 0x00-0x5b
    Vec3 vec;                             // 0x5c-0x67
    unsigned char pad_68[0x8e - 0x68];    // 0x68-0x8d
    short unk_8E;                         // 0x8e-0x8f
    unsigned char pad_90[0x190 - 0x90];   // 0x90-0x18f
    unsigned int unk_190;                 // 0x190-0x193
    unsigned char pad_194[0x2a0 - 0x194]; // 0x194-0x29f
    unsigned char pad_2A0[0x334 - 0x2a0]; // 0x2a0-0x333
    unsigned char pad_334[0x564 - 0x334]; // 0x334-0x563
} UnkStruct_020c1fc8;

int func_020c1fc8(UnkStruct_020c1fc8 *self)
{
    Vec3 vec;
    Vec3 *vp;
    short s;

    if (func_02016884((void *) ((char *) self + 0x334), 0x122, (void *) ((char *) self + 0x2a0))) {
        s = self->unk_8E;
        vp = &self->vec;
        vec.x = self->vec.x;
        vec.y = vp->y;
        vec.z = vp->z;
        if (((self->unk_190 << 4) >> 16) == 7) {
            func_020912d4(0x39, &vec, &s, 0);
        }
        if (((self->unk_190 << 4) >> 16) == 9) {
            func_020912d4(0x38, &vec, &s, 0);
        }
        if (func_02019de8((void *) ((char *) self + 0x564))) {
            func_02019c20((void *) ((char *) self + 0x564), 1, 0x123, 1, data_020c80f8, 0);
        }
    }
    if (func_02016884((void *) ((char *) self + 0x334), 0x123, (void *) ((char *) self + 0x2a0))) {
        if (func_02019de8((void *) ((char *) self + 0x564))) {
            func_020c26b4(self, 1);
        }
    }
    return 1;
}
