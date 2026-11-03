/* mailbox_scene_2: 6 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229cbdc @ 0x0229cbdc, 0x74 bytes, Thumb
 * func_ov106_0229cba8 @ 0x0229cba8, 0x34 bytes, Thumb
 * func_ov106_0229cb58 @ 0x0229cb58, 0x50 bytes, Thumb
 * func_ov106_0229caf4 @ 0x0229caf4, 0x64 bytes, Thumb
 * func_ov106_0229ca90 @ 0x0229ca90, 0x64 bytes, Thumb
 * func_ov106_0229ca5c @ 0x0229ca5c, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x2d];
    unsigned char unk_BB;
    char pad_BC[0x21e4];
    char unk_22A0[1];
} UnkStruct_0229cbdc;

struct UnkStruct_0229ca90 {
    char pad_00[0xBD];
    unsigned char unk_BD;
    char pad_BE[0x21E2]; // up to 0x22A0
    char unk_22A0;
    char pad_22A1[0x63]; // up to 0x2304
    char unk_2304;
};

struct UnkStruct_0229ca5c {
    char pad_00[0x22a0];
    int unk_22A0;
};

extern int func_ov106_0229c364(void *self, int n);
extern int func_ov106_0229cc84(void *self);
extern int func_ov106_0229cc74(void *self);
extern void func_ov106_0229c344(void *self, int n);
extern void func_ov002_0220a05c(char *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220a08c(unsigned char *, int, int, int);
extern int func_ov002_022090e4(void *ptr, int val);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char val);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_0208e4c0(void *ptr, int val);
extern void func_ov002_0220a374(void *p, int v);

void func_ov106_0229cbdc(UnkStruct_0229cbdc *self)
{
    int a, b, flag;
    if (func_ov106_0229c364(self, 8)) {
        a = func_ov106_0229cc84(self);
        b = func_ov106_0229cc74(self);
        func_ov002_0220a0b4((void *) self->unk_22A0, a, b);
        func_ov106_0229c344(self, 8);
    } else {
        a = func_ov106_0229cc84(self);
        b = func_ov106_0229cc74(self);
        flag = 1;
        func_ov002_0220a05c(self->unk_22A0, a, b, 3, flag);
        self->unk_BB = self->unk_8D;
        func_ov002_02208098((void *) (self), 13);
    }
}

void func_ov106_0229cba8(void *p, int a, int b)
{
    func_ov002_0220a05c((char *) ((char *) p + 0x22a0), a, b, 3, 1);
    ((unsigned char *) p)[0xbb] = ((unsigned char *) p)[0x8d];
    func_ov002_02208098((void *) (p), 0xd);
}

void func_ov106_0229cb58(unsigned char *p)
{
    int a = func_ov002_02208ae4((void *) (p + 0x2304));
    int b = func_ov002_02208ad8((void *) (p + 0x2304), *(unsigned char *) (p + 0xbd));
    func_ov002_0220a08c(p + 0x22a0, a, b, 2);
    *(unsigned char *) (p + 0xbb) = *(unsigned char *) (p + 0x8d);
    func_ov002_02208098((void *) (p), 0xd);
}

int func_ov106_0229caf4(char *self)
{
    int a, b;
    self[0xBC] = 4;
    self[0xBD] = func_ov002_022090e4(self + 0x2304, 1);
    a = func_ov002_02208ae4(self + 0x2304);
    b = func_ov002_02208ad8(self + 0x2304, self[0xBD]);
    func_ov002_0220a0b4(self + 0x22A0, a, b);
    func_0208e4c0(self + 0x22A0, 8);
    return (int) func_ov002_02208098((void *) (self), 0x17);
}

void func_ov106_0229ca90(struct UnkStruct_0229ca90 *self)
{
    int t1, t2;

    if (func_ov106_0229c364(self, 0x10000)) {
        self->unk_BD = 1;
    } else {
        self->unk_BD = 0;
    }

    t1 = func_ov002_02208ae4(&self->unk_2304);
    t2 = func_ov002_02208ad8(&self->unk_2304, self->unk_BD);
    func_ov002_0220a0b4(&self->unk_22A0, t1, t2);
    func_ov002_0220a374(&self->unk_22A0, 7);
}

void func_ov106_0229ca5c(struct UnkStruct_0229ca5c *self)
{
    int v1 = func_ov106_0229cc84(self);
    int v2 = func_ov106_0229cc74(self);
    func_ov002_0220a0b4(&self->unk_22A0, v1, v2);
    func_ov002_0220a374(&self->unk_22A0, 1);
}
