/* func_ov004_0223de70 @ 0x0223de70, 0xd8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[12];
} Mtx;

typedef struct UnkStruct_0223de70 {
    char unk_00[8];
    unsigned int unk_08;
    char unk_0C[0x184 - 0xc];
    Mtx unk_184;
} UnkStruct_0223de70;

extern int data_ov004_02259a14;

extern void func_ov004_0223e3ec(UnkStruct_0223de70 *self);
extern void func_ov004_0223dd90(UnkStruct_0223de70 *self);
extern void func_ov004_0223d82c(UnkStruct_0223de70 *self);
extern void func_ov004_0223e1f0(UnkStruct_0223de70 *self);
extern void func_ov004_0223de14(UnkStruct_0223de70 *self);
extern void func_02055124(char *p);
extern void func_ov004_0223df48(UnkStruct_0223de70 *self);
extern int func_0203f8d0(char *a, char *b);
extern void func_020031d4(UnkStruct_0223de70 *self, Mtx *m);
extern void func_ov004_0223dccc(UnkStruct_0223de70 *self);
extern void func_ov004_0223e3d4(UnkStruct_0223de70 *self, int k);

int func_ov004_0223de70(UnkStruct_0223de70 *self)
{
    Mtx m;
    unsigned int n;

    *((unsigned char *) self + 0x263) = 0;
    n = self->unk_08;
    if (n >= 0x1f) {
        if (*(int *) ((char *) self + 0x110) == 1) {
            if (data_ov004_02259a14 == 0) {
                func_ov004_0223e3ec(self);
            }
            func_ov004_0223dd90(self);
            func_ov004_0223d82c(self);
            func_ov004_0223e1f0(self);
            func_ov004_0223de14(self);
            if (*((unsigned char *) self + 0x22a) != 0) {
                func_02055124((char *) self + 0x120);
            }
        } else {
            self->unk_08 = n - 1;
        }
    } else if (*(int *) ((char *) self + 0x110) == 1) {
        self->unk_08 = n + 2;
        func_ov004_0223df48(self);
    } else {
        self->unk_08 = n - 1;
    }
    if (self->unk_08 != 0) {
        *(short *) ((char *) self + 0xd0) = (short) func_0203f8d0((char *) self + 0xc4, (char *) self + 0x5c);
        func_020031d4(self, &m);
        self->unk_184 = m;
    } else {
        func_ov004_0223dccc(self);
    }
    if (*((unsigned char *) self + 0x263) == 0) {
        func_ov004_0223e3d4(self, 0);
    }
    return 1;
}
