/* birthday_screen_5: 3 functions, module ov137
 * mwccarm 1.2/base -O4,s
 * func_ov137_0229d2f4 @ 0x0229d2f4, 0x1e bytes, Thumb
 * func_ov137_0229d2d8 @ 0x0229d2d8, 0x1a bytes, Thumb
 * func_ov137_0229d284 @ 0x0229d284, 0x54 bytes, Thumb
 */

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229d2f4;

extern void func_ov137_0229cf68(void *self);
extern unsigned char *func_ov002_022080a0(void *self, unsigned char arg1);
extern int func_020ee45c(int);
extern void func_ov092_0229929c(int);
extern void func_ov137_0229cf48(int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern int func_ov137_0229c574(void *p, int a);
extern int func_ov002_02207f60(void *p);
extern void func_ov134_0229b220(void *p, int a, int b);
extern void func_ov002_0220ad18(void *p, int a);

int func_ov137_0229d2f4(UnkStruct_0229d2f4 *self)
{
    func_ov137_0229cf68(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov137_0229d2d8(int a)
{
    func_ov092_0229929c(func_020ee45c(a));
    func_ov137_0229cf48(a);
    return 1;
}

int func_ov137_0229d284(void *self)
{
    char *p;
    int ret;

    if (func_0206fe54()) {
        p = (char *) self;
        p += 0x94;
        func_ov002_02209eb8(p);
    }
    if (!func_ov137_0229c574(self, 1)) {
        return 0;
    }

    ret = func_ov002_02207f60(self);
    func_ov134_0229b220((char *) self + 0x2c4, 0, ret);

    ret = func_ov002_02207f60(self);
    self = (char *) self + 0xf8;
    func_ov002_0220ad18(self, ret);

    return 1;
}
