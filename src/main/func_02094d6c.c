/* func_02094d6c @ 0x02094d6c, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea6e0(int *v, int s);
extern void VEC_Add(int *a, int *b, int *c);
extern int func_020ea838(int *v);

typedef struct Vec {
    int x, y, z, w;
} Vec;

typedef struct Input {
    int a[3];
    short b;
} Input;

typedef struct UnkStruct_02094d6c {
    char pad_00[0x18];
    Vec **obj;
    char pad_1C[0x04];
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x10];
    short unk_3C;
    short unk_3E;
    short unk_40;
} UnkStruct_02094d6c;

void func_02094d6c(UnkStruct_02094d6c *self, Input *in, int *v2, int *v3)
{
    int src[3];
    int copy[3];
    int cand[3];

    src[0] = in->a[0];
    src[1] = in->a[1];
    src[2] = in->a[2];

    if (v2) {
        copy[0] = v2[0];
        copy[1] = v2[1];
        copy[2] = v2[2];
        func_020ea6e0(copy, in->b);
        VEC_Add(src, copy, src);
    }

    self->unk_20 = src[0] + (*self->obj)->y;
    self->unk_24 = src[1] + (*self->obj)->z;
    self->unk_28 = src[2] + (*self->obj)->w;

    if (v3) {
        cand[0] = v3[0];
        cand[1] = v3[1];
        cand[2] = v3[2];
        func_020ea6e0(cand, in->b);
        if (func_020ea838(cand) != 0) {
            int c1 = cand[1];
            int c2 = cand[2];
            int c0 = cand[0];
            self->unk_3C = (short) c0;
            self->unk_3E = (short) c1;
            self->unk_40 = (short) c2;
        }
    }
}
