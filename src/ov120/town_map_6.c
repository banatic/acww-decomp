/* town_map_6: 10 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229b97c @ 0x0229b97c, 0x60 bytes, Thumb
 * func_ov120_0229b900 @ 0x0229b900, 0x7c bytes, Thumb
 * func_ov120_0229b8d0 @ 0x0229b8d0, 0x30 bytes, Thumb
 * func_ov120_0229b7f8 @ 0x0229b7f8, 0xd8 bytes, Thumb
 * func_ov120_0229b7cc @ 0x0229b7cc, 0x2c bytes, Thumb
 * func_ov120_0229b784 @ 0x0229b784, 0x48 bytes, Thumb
 * func_ov120_0229b740 @ 0x0229b740, 0x44 bytes, Thumb
 * func_ov120_0229b71c @ 0x0229b71c, 0x24 bytes, Thumb
 * func_ov120_0229b6e4 @ 0x0229b6e4, 0x38 bytes, Thumb
 * func_ov120_0229b6b8 @ 0x0229b6b8, 0x2c bytes, Thumb
 */

typedef struct UnkStruct_0229b7f8 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0x11];
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char unk_AE;
} UnkStruct_0229b7f8;

extern void *data_021fbe94;
extern const char data_ov120_0229c6b0[];
extern const char data_ov120_0229c6c8[];
extern const char data_ov120_0229c6e4[];
extern int func_02002d14(const char *data, void *obj, int a, int b, int c, int d);
extern int func_02002c6c(const char *data, void *obj, int a, int b, int c, int d);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208054(void *arg, int n);
extern unsigned char *func_ov002_02208098(void *arg, unsigned char value);
extern void func_ov120_0229b604(void *arg);
extern int func_ov120_0229a9b4(void *arg);
extern int func_ov120_0229aacc(void *arg);
extern int func_ov120_0229aed8(void *arg);
extern int func_ov120_0229b100(void *arg);
extern void *func_0208e95c(void *addr, int n);
extern void func_ov120_0229b64c(void *);
extern void func_ov120_0229aa80(void *);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *self);
extern int func_ov120_0229a584(void *self, int val);
extern int func_ov120_0229a448(void *self, int num);
extern void func_ov120_0229abdc(void *self, unsigned int val);
extern void func_ov120_0229a730(void *self);
extern void func_ov120_0229a710(void *self);
extern void func_ov120_0229adc4(void *self, int num);
extern void func_ov120_0229ad5c(void *self, int num);
extern void func_ov120_0229a45c(void *self);
extern unsigned char func_ov120_0229ae78(void *self, unsigned char a, unsigned char b);
extern void func_ov120_0229a438(void *self, unsigned int val);
extern unsigned short data_021fbe40[];
extern void func_ov120_0229c044(void *);
extern int func_ov002_02209f64(void *);
extern int func_0208e484(void *p);
extern int func_ov120_0229a4bc(void *p);
extern void func_ov120_0229abec(void *p, int a);
extern void func_ov120_0229a6f0(void *p);
extern void func_ov120_0229a6d0(void *);
extern int func_0208e930(void *);
extern void func_ov120_0229aa30(void *p);
extern void func_ov120_0229a428(void *ptr, int param);

void func_ov120_0229b97c(void)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov120_0229c6b0, p, 8, 6, 6, 14);
    func_02002c6c(data_ov120_0229c6c8, p, 8, 0xc0, 0xc0, 0xff);
    func_02002c6c(data_ov120_0229c6e4, p, 8, 0x180, 0x180, 0x1ff);
}

void func_ov120_0229b900(void *arg)
{
    unsigned int flag;

    if (func_ov002_02208054(arg, 1) != 0) {
        func_ov120_0229b604(arg);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (flag > 0) {
        if (func_ov120_0229a9b4(arg) != 0) {
            return;
        }
        if (func_ov120_0229aacc(arg) != 0) {
            func_0208e95c((char *) arg + 0x674, 2);
            func_ov002_02208098(arg, 1);
        } else {
            if (func_ov120_0229aed8(arg) != 0) {
                return;
            }
            if (func_ov120_0229b100(arg) != 0) {
                return;
            }
        }
    }
}

void func_ov120_0229b8d0(void *p)
{
    if (!data_021fbdd8) {
        func_0208e95c((char *) p + 0x674, 3);
        func_ov120_0229b64c(p);
    }
    func_ov120_0229aa80(p);
}

void func_ov120_0229b7f8(UnkStruct_0229b7f8 *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov120_0229b64c(self);
        return;
    }
    if (func_ov120_0229a584(self, func_ov002_02208008(self)) != 0) {
        if (func_ov120_0229a448(self, 8) != 0) {
            if (self->unk_AB >= 2 && self->unk_AB <= 7) {
                func_ov120_0229abdc(self, self->unk_98 & ~0xf);
            }
        }
        func_ov120_0229a730(self);
    } else {
        unsigned short cur = data_021fbe40[1];
        if (cur & 1) {
            func_ov120_0229a710(self);
            return;
        }
        if (!(cur & 0x800)) {
            return;
        }
        func_ov120_0229adc4(self, 0);
        func_ov120_0229ad5c(self, 0xe);
        if (self->unk_AB >= 2 && self->unk_AB <= 7) {
            func_ov120_0229a45c(self);
        }
        self->unk_AC = func_ov120_0229ae78(self, self->unk_AD, self->unk_AE);
        func_ov120_0229a438(self, 0x800);
        func_ov002_02208098(self, 9);
        func_ov120_0229a730(self);
    }
}

void func_ov120_0229b7cc(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x6bc) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0xaa));
        func_ov120_0229c044(self);
    }
}

void func_ov120_0229b784(void *p)
{
    if (func_0208e484((char *) p + 0x6bc) != 0) {
        int v = func_ov120_0229a4bc(p);
        if (v == 1) {
            return;
        }
        if (v == 2) {
            func_ov120_0229abec(p, 0);
            *((unsigned char *) p + 0xa3) = 0xff;
            func_ov120_0229a6f0(p);
            return;
        }
        func_ov120_0229a6f0(p);
    }
}

void func_ov120_0229b740(void *p)
{
    if (func_0208e484((char *) p + 0x6bc)) {
        func_ov120_0229a6d0(p);
        if (func_ov120_0229a448(p, 0x800)) {
            func_ov002_02208098(p, 9);
        } else {
            func_ov002_02208098(p, 2);
        }
    }
}

void func_ov120_0229b71c(void *arg0)
{
    if (func_0208e930((char *) arg0 + 0x674) != 0) {
        func_ov002_02208098(arg0, 7);
    }
}

void func_ov120_0229b6e4(void *param)
{
    if (!((*(unsigned short *) data_021fbe40) & 1)) {
        func_0208e95c((char *) param + 0x674, 3);
        func_ov002_02208098(param, 8);
    } else {
        func_ov120_0229aa30(param);
    }
}

void func_ov120_0229b6b8(void *obj)
{
    if (func_0208e930((char *) obj + 0x674)) {
        func_ov120_0229a6f0(obj);
        func_ov120_0229a428(obj, 0x1000);
    }
}
