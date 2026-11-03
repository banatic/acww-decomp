/* pockets_screen_5: 5 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229dd94 @ 0x0229dd94, 0x44 bytes, Thumb
 * func_ov096_0229dd44 @ 0x0229dd44, 0x50 bytes, Thumb
 * func_ov096_0229dce0 @ 0x0229dce0, 0x64 bytes, Thumb
 * func_ov096_0229dc7c @ 0x0229dc7c, 0x64 bytes, Thumb
 * func_ov096_0229dc48 @ 0x0229dc48, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0xbb];
    unsigned char unk_BB;
    unsigned char unk_BC;
    char pad_BD[0x2500 - 0xbd];
    char unk_2500[0x64];
    char unk_2564[1];
} UnkStruct_0229dce0;

typedef struct {
    unsigned char pad_00[0xbc];
    unsigned char flag;
    unsigned char pad_BD[0x2500 - 0xbd];
    char obj_2500;
    unsigned char pad_2501[0x2564 - 0x2501];
    char obj_2564;
} UnkStruct_0229dc7c;

extern int func_ov096_0229de0c(unsigned char *p);
extern int func_ov096_0229ddfc(unsigned char *p);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220a08c(unsigned char *ptr, int a, int b, int c);
extern int func_ov002_022090e4(void *ptr, int a);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char a);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_0208e4c0(void *ptr, int a);
extern int func_ov096_0229c2fc(void *, int);
extern void func_ov002_0220a374(void *, int);

void func_ov096_0229dd94(unsigned char *p)
{
    int v1 = func_ov096_0229de0c(p);
    int v2 = func_ov096_0229ddfc(p);
    func_ov002_0220a05c(p + 0x2500, v1, v2, 3, 1);
    p[0xba] = p[0x8d];
    func_ov002_02208098((void *) (p), 0xf);
}

void func_ov096_0229dd44(unsigned char *self)
{
    int res1;
    int res2;

    res1 = func_ov002_02208ae4((void *) (self + 0x2564));
    res2 = func_ov002_02208ad8((void *) (self + 0x2564), self[0xbc]);
    func_ov002_0220a08c(self + 0x2500, res1, res2, 2);
    self[0xba] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xf);
}

void func_ov096_0229dce0(UnkStruct_0229dce0 *p)
{
    int v1, v2;
    p->unk_BB = 0x22;
    p->unk_BC = func_ov002_022090e4(p->unk_2564, 1);
    v1 = func_ov002_02208ae4(p->unk_2564);
    v2 = func_ov002_02208ad8(p->unk_2564, p->unk_BC);
    func_ov002_0220a0b4(p->unk_2500, v1, v2);
    func_0208e4c0(p->unk_2500, 8);
    func_ov002_02208098((void *) (p), 30);
}

void func_ov096_0229dc7c(UnkStruct_0229dc7c *arg)
{
    if (func_ov096_0229c2fc(arg, 0x40000)) {
        arg->flag = 1;
    } else {
        arg->flag = 0;
    }
    {
        int v1 = func_ov002_02208ae4(&arg->obj_2564);
        int v2 = func_ov002_02208ad8(&arg->obj_2564, arg->flag);
        func_ov002_0220a0b4(&arg->obj_2500, v1, v2);
    }
    func_ov002_0220a374(&arg->obj_2500, 7);
}

void func_ov096_0229dc48(int self)
{
    int r4;
    int r2;
    int r0;
    int r5 = self;

    r4 = func_ov096_0229de0c((unsigned char *) ((void *) self));
    r0 = r5;
    r2 = func_ov096_0229ddfc((unsigned char *) r0);
    r0 = r5 + 0x2500;
    func_ov002_0220a0b4((void *) r0, r4, r2);
    r0 = r5 + 0x2500;
    func_ov002_0220a374((void *) r0, 1);
}
