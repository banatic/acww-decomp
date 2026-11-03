/* birthday_screen_4: 11 functions, module ov137
 * mwccarm 1.2/base -O4,s
 * func_ov137_0229d0c4 @ 0x0229d0c4, 0x1c bytes, Thumb
 * func_ov137_0229d0c0 @ 0x0229d0c0, 0x4 bytes, Thumb
 * func_ov137_0229d0bc @ 0x0229d0bc, 0x4 bytes, Thumb
 * func_ov137_0229d0ac @ 0x0229d0ac, 0x10 bytes, Thumb
 * func_ov137_0229d050 @ 0x0229d050, 0x5a bytes, Thumb
 * func_ov137_0229d028 @ 0x0229d028, 0x28 bytes, Thumb
 * func_ov137_0229cff0 @ 0x0229cff0, 0x38 bytes, Thumb
 * func_ov137_0229cfc0 @ 0x0229cfc0, 0x30 bytes, Thumb
 * func_ov137_0229cfa0 @ 0x0229cfa0, 0x20 bytes, Thumb
 * func_ov137_0229cf68 @ 0x0229cf68, 0x38 bytes, Thumb
 * func_ov137_0229cf48 @ 0x0229cf48, 0x20 bytes, Thumb
 */

struct UnkStruct_0229cf68 {
    char pad_00[0x2c4];
    unsigned char unk_2C4;
    char pad_2C5[0x2b74 - 0x2c4 - 1];
    unsigned short unk_2B74;
    char pad_2B76[1];
    unsigned char unk_2B77;
};

extern void func_ov137_0229cf30(void *);
extern void func_ov137_0229d0e0(void *);
extern void func_ov137_0229cf28(void *);
extern void func_020ee470(void *parameter0);
extern void func_ov137_0229ceb0(void);
extern void func_ov137_0229ce90(void *self);
extern void func_ov137_0229ce70(void *self);
extern void func_02002708(int);
extern void func_ov137_0229c564(void *self, int);
extern int func_ov002_0220ab84(void *self, int);
extern void func_ov002_02208090(void *self, int);
extern void func_ov002_02207f20(void *self, int, int, int, int);
extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov137_0229c978(void *p);
extern void *func_020ee45c(void *arg0);
extern void func_ov092_02299324(void *arg0, int arg1, int arg2);
extern void func_ov002_02207f04(void *arg0, int arg1, int arg2, int arg3, int arg4);
extern int func_ov002_02207f3c(int, int);
extern void func_020027f0(int);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov134_0229bd38(void *addr, int a, int b, int c, int d);
extern void func_ov134_0229bcf0(void *);
extern void func_ov002_0220af74(void *);

void func_ov137_0229cfa0(void *p);

int func_ov137_0229d0c4(void *p)
{
    func_ov137_0229cf30(p);
    func_ov137_0229d0e0(p);
    func_ov137_0229cf28(p);
    return 1;
}

int func_ov137_0229d0c0(void)
{
    return 1;
}

int func_ov137_0229d0bc(void)
{
    return 1;
}

int func_ov137_0229d0ac(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov137_0229d050(void *self)
{
    func_ov137_0229ceb0();
    func_ov137_0229ce90(self);
    func_ov137_0229ce70(self);
    func_ov002_02207f20(self, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov137_0229cfa0(self);
    func_ov137_0229c564(self, 1);
    func_ov002_0220ab84((char *) self + 0xf8, 0x21);
    func_ov002_02208090(self, 1);
}

void func_ov137_0229d028(void *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0(p, 2);
        func_ov137_0229c978(p);
    }
    func_ov137_0229cfa0(p);
}

void func_ov137_0229cff0(void *arg0)
{
    int zero = 0;

    func_ov092_02299324(func_020ee45c(arg0), 0x44, 1);
    func_ov002_02207f04(arg0, 10, zero, zero, 0x30);
    func_ov137_0229cfa0(arg0);
    func_ov002_02208090(arg0, 3);
}

void func_ov137_0229cfc0(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) param, 5);
    } else {
        func_ov137_0229cfa0((void *) param);
    }
}

void func_ov137_0229cfa0(void *p)
{
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
}

void func_ov137_0229cf68(struct UnkStruct_0229cf68 *self)
{
    func_ov134_0229bd38(&self->unk_2C4, 2, 6, 4, 3);
    self->unk_2B77 = 0;
    self->unk_2B74 = 0;
}

void func_ov137_0229cf48(void *self)
{
    func_ov134_0229bcf0((char *) self + 0x2c4);
    func_ov002_0220af74((char *) self + 0xf8);
}
