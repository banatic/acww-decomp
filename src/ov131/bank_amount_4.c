/* bank_amount_4: 9 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229b490 @ 0x0229b490, 0x8 bytes, Thumb
 * func_ov131_0229b474 @ 0x0229b474, 0x1c bytes, Thumb
 * func_ov131_0229b43c @ 0x0229b43c, 0x38 bytes, Thumb
 * func_ov131_0229b404 @ 0x0229b404, 0x38 bytes, Thumb
 * func_ov131_0229b3f4 @ 0x0229b3f4, 0x10 bytes, Thumb
 * func_ov131_0229b3d4 @ 0x0229b3d4, 0x20 bytes, Thumb
 * func_ov131_0229b338 @ 0x0229b338, 0x9c bytes, Thumb
 * func_ov131_0229b304 @ 0x0229b304, 0x34 bytes, Thumb
 * func_ov131_0229b274 @ 0x0229b274, 0x90 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xf8];
    unsigned char unk_F8;
    unsigned char pad_F9[0x2c4 - 0xf8 - 1];
    unsigned char unk_2C4;
} UnkStruct_0229b43c;

typedef struct {
    char pad_00[0xf8];
    void *unk_F8;
    char pad_FC[0x1c8];
    void *unk_2C4;
} UnkStruct_0229b338;

struct UnkStruct_0229b274 {
    char pad_00[2];
    unsigned short flags;
};

extern void func_ov002_0220af74(void *);
extern void func_ov130_0229a32c(void *);
extern void func_ov130_0229a2b4(void *);
extern int func_ov130_02299ddc(void *);
extern void func_ov002_0220a658(void *, int);
extern void func_ov002_0220a63c(void *, int);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov130_0229a4c8(int a);
extern void func_ov130_0229a3a0(void *);
extern void func_ov002_0220af94(void *receiver);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208054(void *self, int arg);
extern void func_ov131_0229b0f0(void *self);
extern int func_ov002_0220a784(void *ptr, int idx);
extern int func_ov131_0229b07c(void *self);
extern void func_ov131_0229b04c(void *self);
extern int func_ov130_0229a278(void *ptr, unsigned char a, unsigned char b);
extern void func_ov130_0229a254(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov130_0229a24c(void *p);
extern int func_ov130_0229a224(void *p);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *p);
extern int func_ov130_0229a0a4(void *p, int a);
extern int func_ov130_02299d98(void *p);
extern void func_ov131_0229b10c(void *p);
extern void func_ov131_0229af74(void *p);
extern void func_ov131_0229afbc(void *p);
extern void func_ov131_0229af0c(void *p);
extern struct UnkStruct_0229b274 data_021fbe40;

void func_ov131_0229b43c(UnkStruct_0229b43c *self);

void func_ov131_0229b490(void *argument0)
{
    func_ov131_0229b43c((UnkStruct_0229b43c *) argument0);
}

void func_ov131_0229b474(void *self)
{
    func_ov002_0220af74((char *) self + 0xf8);
    func_ov130_0229a32c((char *) self + 0x2c4);
}

void func_ov131_0229b43c(UnkStruct_0229b43c *self)
{
    int result;
    func_ov130_0229a2b4(&self->unk_2C4);
    result = func_ov130_02299ddc(&self->unk_2C4);
    if (result == 0) {
        func_ov002_0220a658(&self->unk_F8, 6);
    } else {
        func_ov002_0220a63c(&self->unk_F8, 6);
    }
}

void func_ov131_0229b404(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov131_0229b3f4(int a)
{
    func_ov130_0229a4c8(a + 0x2c4);
}

void func_ov131_0229b3d4(void *arg0)
{
    func_ov130_0229a3a0((char *) arg0 + 0x2c4);
    arg0 = (char *) arg0 + 0xf8;
    func_ov002_0220af94(arg0);
}

void func_ov131_0229b338(UnkStruct_0229b338 *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov131_0229b0f0(self);
        return;
    }

    {
        unsigned int cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        if (cond > 0) {
            if (func_ov002_0220a784(&self->unk_F8, 6) != 0) {
                func_ov131_0229b07c(self);
                return;
            } else {
                if (func_ov002_0220a784(&self->unk_F8, 7) != 0) {
                    func_ov131_0229b04c(self);
                    return;
                } else {
                    if (func_ov130_0229a278(&self->unk_2C4, data_021f6c58, data_021f6c54) != 0xd) {
                        func_ov130_0229a254(&self->unk_2C4);
                        func_ov002_02208098((void *) (self), 1);
                    }
                }
            }
        }
    }
}

void func_ov131_0229b304(void *param)
{
    if (data_021fbdd8 == 0) {
        func_ov130_0229a24c((char *) param + 0x2c4);
        func_ov002_02208098((void *) (param), 0);
    } else {
        func_ov130_0229a224((char *) param + 0x2c4);
    }
}

void func_ov131_0229b274(void *p)
{
    unsigned short flags;

    if (func_ov002_02208014(p) != 0) {
        func_ov131_0229b10c(p);
        return;
    }

    if (func_ov130_0229a0a4((void *) ((char *) p + 0x2c4), func_ov002_02208008(p)) != 0) {
        func_ov131_0229af74(p);
        return;
    }

    flags = data_021fbe40.flags;
    if (flags & 8) {
        if (func_ov131_0229b07c(p) != 0) {
            func_ov131_0229afbc(p);
        }
        return;
    }
    if (flags & 1) {
        func_ov131_0229af0c(p);
        return;
    }
    if (flags & 2) {
        if (func_ov130_02299d98((void *) ((char *) p + 0x2c4)) == 0) {
            func_ov131_0229afbc(p);
            func_ov131_0229b04c(p);
        }
        return;
    }
}
