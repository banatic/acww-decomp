/* letter_write_scene_7: 5 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_022a053c @ 0x022a053c, 0x94 bytes, Thumb
 * func_ov122_022a04ec @ 0x022a04ec, 0x50 bytes, Thumb
 * func_ov122_022a04bc @ 0x022a04bc, 0x30 bytes, Thumb
 * func_ov122_022a0488 @ 0x022a0488, 0x34 bytes, Thumb
 * func_ov122_022a03b0 @ 0x022a03b0, 0xd8 bytes, Thumb
 */

typedef struct UnkStruct_022a03b0 UnkStruct_022a03b0;

struct UnkStruct_022a03b0 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x29];
    unsigned char b6;
    unsigned char b7;
    unsigned char pad_B8[4];
    void *unk_BC;
    unsigned char pad_C0[0x3ce8 - 0xc0];
    unsigned char unk_3CE8;
    unsigned char pad_3CE9[0x42b0 - 0x3ce9];
    unsigned char sub;
};

extern int func_0206f56c(void);
extern void func_ov122_0229efd8(void *, int);
extern void func_ov122_0229f0a8(void *);
extern int func_ov002_02208014(void *receiver);
extern void func_ov122_0229ff94(void *);
extern int func_ov002_02208008(void *);
extern int func_ov002_02209044(void *, int, void *, int);
extern void func_ov122_0229f104(void *);
extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned short data_021fbe40[];
extern int func_0208e484(void *ptr);
extern void func_ov002_022090b0(void *ptr, unsigned char b);
extern unsigned char func_ov002_02208a8c(void *ptr, unsigned char b1, unsigned char b2);
extern int func_0206fe54(void);
extern void func_ov122_0229ff2c(int);
extern int func_ov002_02208e28(int);
extern int func_ov002_0220909c(const unsigned char *p);
extern void func_ov002_022096d8(unsigned char *p, int v);
extern void func_ov122_0229f2d0(unsigned char *p);
extern int func_ov002_02208e18(void *);
extern int func_ov002_02208a24(void *, void *, unsigned char);
extern void func_0206e1d8(void *, void *);
extern void func_ov122_022a15b8(UnkStruct_022a03b0 *, int, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern unsigned int func_ov002_02208ad0(void *);
extern void func_ov122_0229f0dc(UnkStruct_022a03b0 *, int);
extern int func_ov122_0229efe8(UnkStruct_022a03b0 *, int);
extern void func_ov122_022a1e00(UnkStruct_022a03b0 *);

void func_ov122_022a053c(void *param)
{
    int tmp;
    unsigned short flags;

    if (func_0206f56c()) {
        func_ov122_0229efd8(param, 0x2000);
        func_ov122_0229f0a8(param);
        return;
    }
    if (func_ov002_02208014(param)) {
        func_ov122_0229ff94(param);
        return;
    }
    tmp = func_ov002_02208008(param);
    if (func_ov002_02209044((char *) param + 0x42b0, tmp, (char *) param + 0xb6, 0)) {
        func_ov122_0229f104(param);
    }

    flags = data_021fbe40[1];
    if (flags & 1) {
        func_ov002_0220a1dc((char *) param + 0x4058);
        func_ov002_02208098((void *) (param), 0x15);
    } else if (flags & 2) {
        func_ov122_0229f0a8(param);
    }
}

void func_ov122_022a04ec(char *param)
{
    if (func_0208e484((void *) (param + 0x4058)) != 0) {
        func_ov002_022090b0((void *) (param + 0x42b0), *(unsigned char *) (param + 0xb6));
        *(unsigned char *) (param + 0xb6) = func_ov002_02208a8c((void *) (param + 0x42b0), *(unsigned char *) (param + 0xb7),
                                                                *(unsigned char *) (param + 0xb6));
        func_ov002_02208098((void *) ((void *) param), 0x17);
    }
}

void func_ov122_022a04bc(int param)
{
    if (func_ov002_02208e28(param + 0x42b0) != 0) {
        if (func_0206fe54() != 0) {
            func_ov122_0229ff2c(param);
        } else {
            func_ov122_0229ff94((void *) param);
        }
    }
}

void func_ov122_022a0488(unsigned char *p)
{
    if (func_ov002_0220909c(p + 0x42b0) != 0) {
        func_ov002_022096d8(p + 0x42b0, 0);
        func_ov002_02208098((void *) (p), 0x18);
        func_ov122_0229f2d0(p);
    }
}

void func_ov122_022a03b0(UnkStruct_022a03b0 *self)
{
    int r;

    if (func_ov002_02208e18(&self->sub) == 0) {
        return;
    }

    r = func_ov002_02208a24(&self->sub, self->unk_BC, self->b6);

    switch (r) {
        case 1:
            func_0206e1d8(&self->unk_3CE8, self->unk_BC);
            func_ov122_022a15b8(self, 1, 0);
            self->unk_8C = 0xa;
            func_ov002_022080a0((void *) (self), 1);
            break;

        case 2:
            self->b7 = self->b7 + 1;
            if (self->b7 >= func_ov002_02208ad0(&self->sub)) {
                self->b7 = 0;
            }
            func_ov122_0229f0dc(self, 0);
            break;

        case 3:
            if (func_ov122_0229efe8(self, 0x2000) != 0) {
                func_ov122_022a1e00(self);
            } else {
                self->unk_8C = 0xa;
                func_ov002_022080a0((void *) (self), 1);
            }
            break;

        default:
            self->unk_8C = 0xa;
            func_ov002_022080a0((void *) (self), 1);
            break;
    }
}
