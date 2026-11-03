/* my_designs_8: 10 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229b3a4 @ 0x0229b3a4, 0x3c bytes, Thumb
 * func_ov121_0229b37c @ 0x0229b37c, 0x28 bytes, Thumb
 * func_ov121_0229b340 @ 0x0229b340, 0x3c bytes, Thumb
 * func_ov121_0229b31c @ 0x0229b31c, 0x24 bytes, Thumb
 * func_ov121_0229b2a4 @ 0x0229b2a4, 0x78 bytes, Thumb
 * func_ov121_0229b214 @ 0x0229b214, 0x90 bytes, Thumb
 * func_ov121_0229b184 @ 0x0229b184, 0x90 bytes, Thumb
 * func_ov121_0229b148 @ 0x0229b148, 0x3c bytes, Thumb
 * func_ov121_0229b104 @ 0x0229b104, 0x44 bytes, Thumb
 * func_ov121_0229b0e4 @ 0x0229b0e4, 0x20 bytes, Thumb
 */

typedef struct {
    char pad_00[2];
    unsigned short flags;
} Glb;

typedef struct {
    unsigned char pad_00[0xb2];
    unsigned char unk_B2;
    unsigned char unk_B3;
    unsigned char pad_B4[0x3a8 - 0xb4];
    int unk_3A8;
    unsigned char pad_3AC[0x528 - 0x3ac];
    int unk_528;
} UnkStruct_0229b184;

extern int func_ov121_02299fc8(const void *p);
extern int func_ov121_0229bc70(const void *p, int r);
extern void func_ov121_0229a150(const void *p);
extern int func_0208e484(void *object);
extern void func_ov121_0229a190(void *object);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov121_02299a4c(int, int);
extern void func_0200467c(int command);
extern int func_ov002_02209f9c(int);
extern void func_ov121_02299a3c(void *p, int n);
extern int func_ov121_02299a5c(void *p, int n);
extern void func_ov121_0229a450(void *p);
extern int func_ov121_0229ac00(void *p);
extern int func_0206f56c(void);
extern void func_ov121_0229a53c(void *p);
extern int func_ov002_02208014(void *receiver);
extern void func_ov121_0229a358(void *p);
extern int func_ov002_02208008(void *p);
extern int func_ov002_02209044(void *p, int val, void *q, int zero);
extern void func_ov121_0229a294(void *p);
extern void func_ov002_0220a1dc(void *p);
extern void func_ov121_0229a230(void *p);
extern Glb data_021fbe40;
extern int func_ov121_0229ab80(UnkStruct_0229b184 *this, int b3);
extern void func_ov002_02209114(int *field_528, int b3, int r5);
extern int func_0206fe54(void);
extern void func_ov121_0229a1e4(int);
extern int func_ov002_02208e28(int);
extern int func_ov002_0220909c(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_0208e4bc(void *);
extern void func_ov121_0229a1b0(void *);
extern int func_ov002_02208e18(void *);
extern void func_ov121_0229a5c8(void *);

void func_ov121_0229b3a4(const void *self)
{
    if (func_0208e484((void *) ((const char *) self + 0x3a8)) == 0) {
        return;
    }
    {
        int r = func_ov121_02299fc8(self);
        if (r == -1 || func_ov121_0229bc70(self, r) == 0) {
            func_ov121_0229a150(self);
        }
    }
}

void func_ov121_0229b37c(unsigned int param1)
{
    if (func_0208e484((void *) (param1 + 0x3a8)) != 0) {
        func_ov121_0229a190((void *) param1);
        func_ov002_02208098((void *) param1, 4);
    }
}

void func_ov121_0229b340(int param)
{
    if (func_ov002_02209f9c(param + 0x3a8) != 0) {
        func_ov002_02208098((void *) param, 10);
        *(unsigned char *) (param + 0xae) = *(unsigned char *) (param + 0xb1);
        func_ov121_02299a4c(param, 4);
        func_0200467c(0xd);
    }
}

void func_ov121_0229b31c(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x3a8) != 0) {
        func_ov002_02208098(arg0, 5);
    }
}

void func_ov121_0229b2a4(char *p)
{
    if (func_ov002_02209f9c((int) (p + 0x3a8)) != 0) {
        return;
    }
    func_ov121_02299a3c(p, 4);
    if (func_ov121_02299a5c(p, 0x80) != 0) {
        func_ov121_0229a450(p);
        func_ov002_02208098(p, 4);
        func_ov121_02299a3c(p, 0x80);
        func_0200467c(0xe);
    } else {
        unsigned char *src = (unsigned char *) p + 0xb1;
        unsigned char *dst = (unsigned char *) p + 0xaf;
        *dst = *src;
        func_ov121_02299a3c(p, 4);
        if (func_ov121_0229ac00(p) == 0) {
            func_ov121_0229a450(p);
            func_ov002_02208098(p, 4);
        }
    }
}

void func_ov121_0229b214(void *p)
{
    if (func_0206f56c() != 0) {
        func_ov121_0229a53c(p);
        return;
    }
    if (func_ov002_02208014(p) != 0) {
        func_ov121_0229a358(p);
        func_ov002_02208098(p, 3);
        return;
    }
    {
        int tmp = func_ov002_02208008(p);
        if (func_ov002_02209044((char *) p + 0x528, tmp, (char *) p + 0xb3, 0) != 0) {
            func_ov121_0229a294(p);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40.flags;
        if (flags & 1) {
            func_ov002_0220a1dc((char *) p + 0x3a8);
            func_ov002_02208098(p, 0xd);
            return;
        }
        if (flags & 2) {
            func_ov121_0229a230(p);
        }
    }
}

void func_ov121_0229b184(UnkStruct_0229b184 *this)
{
    if (func_0206f56c()) {
        func_ov121_0229a53c((void *) this);
        return;
    }

    if (func_0208e484((void *) (&this->unk_3A8))) {
        int r5;

        this->unk_B2 = (unsigned char) func_ov121_0229ab80(this, this->unk_B3);
        r5 = 1;
        switch (this->unk_B2) {
            case 0:
            case 1:
            case 2:
            case 3:
                func_0200467c(0x50);
                break;
            case 4:
            case 5:
                break;
            case 6:
                r5 = 0;
                break;
        }

        func_ov002_02209114(&this->unk_528, this->unk_B3, r5);
        func_ov002_02208098((void *) this, 0xf);
    }
}

void func_ov121_0229b148(int param)
{
    if (func_ov002_02208e28(param + 0x528) != 0) {
        if (func_0206fe54() != 0) {
            func_ov121_0229a1e4(param);
            func_ov002_02208098((void *) param, 0xc);
        } else {
            func_ov002_02208098((void *) param, 3);
        }
    }
}

void func_ov121_0229b104(char *p)
{
    if (func_ov002_0220909c(p + 0x528)) {
        func_ov002_022096d8(p + 0x528, 0);
        if (func_0208e4bc(p + 0x3a8)) {
            func_ov121_0229a1b0(p);
        }
        func_ov002_02208098(p, 0x10);
    }
}

void func_ov121_0229b0e4(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x528)) {
        func_ov121_0229a5c8(self);
    }
}
