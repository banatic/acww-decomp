/* mailbox_scene_6: 15 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229df98 @ 0x0229df98, 0x34 bytes, Thumb
 * func_ov106_0229df70 @ 0x0229df70, 0x28 bytes, Thumb
 * func_ov106_0229df40 @ 0x0229df40, 0x30 bytes, Thumb
 * func_ov106_0229df14 @ 0x0229df14, 0x2c bytes, Thumb
 * func_ov106_0229dec0 @ 0x0229dec0, 0x54 bytes, Thumb
 * func_ov106_0229de78 @ 0x0229de78, 0x48 bytes, Thumb
 * func_ov106_0229de28 @ 0x0229de28, 0x50 bytes, Thumb
 * func_ov106_0229ddf0 @ 0x0229ddf0, 0x38 bytes, Thumb
 * func_ov106_0229ddb4 @ 0x0229ddb4, 0x3c bytes, Thumb
 * func_ov106_0229dd64 @ 0x0229dd64, 0x50 bytes, Thumb
 * func_ov106_0229dd44 @ 0x0229dd44, 0x20 bytes, Thumb
 * func_ov106_0229dd10 @ 0x0229dd10, 0x34 bytes, Thumb
 * func_ov106_0229dcb0 @ 0x0229dcb0, 0x60 bytes, Thumb
 * func_ov106_0229dc80 @ 0x0229dc80, 0x2e bytes, Thumb
 * func_ov106_0229dc04 @ 0x0229dc04, 0x7c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xbb];
    unsigned char flag;
    unsigned char pad_BC[0x22a0 - 0xbc];
    void *unk_22A0;
} UnkStruct_0229de28;

typedef struct {
    char pad_00[0xbb];
    unsigned char byte_at_bb;
    char pad_BC[0x21e4];
    char field_at_22a0;
    char pad_22A1[0x457];
    char field_at_26f8;
} St;

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned int unk_A0;
    unsigned char pad_A4[0x2654];
    unsigned char unk_26F8;
    unsigned char pad_26F9[0x18bb];
    unsigned char unk_3FB4;
} UnkStruct_0229dcb0;

struct UnkStruct_0229dc80 {
    unsigned char pad_00[0xa0];
    int unk_A0;
};

typedef struct UnkStruct_0229dc04 {
    char pad_00[0x3fb4];
    unsigned char unk_3FB4;
} UnkStruct_0229dc04;

extern int func_0208e484(void *ptr);
extern void func_ov106_0229c378(void *ptr);
extern void func_ov106_0229c9fc(void *ptr);
extern void func_ov106_0229ca3c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02209f9c(void *p);
extern void func_ov106_0229d57c(void *p, unsigned char value);
extern void func_ov106_0229ce0c(const void *);
extern int func_ov106_0229d29c(void *, int argument1);
extern void func_ov106_0229cea8(void *);
extern void func_ov094_022999d8(void);
extern void func_ov106_0229d518(void *, unsigned char, int);
extern int func_ov002_02209f70(void *);
extern void func_ov106_0229cd20(void *, unsigned char);
extern void func_ov106_0229c354(void *, int);
extern int func_ov106_0229c364(UnkStruct_0229de28 *self, int a);
extern void func_ov106_0229c344(UnkStruct_0229de28 *self, int a);
extern void func_ov094_022999c0(void);
extern int func_ov002_02209d8c(void *ptr);
extern void func_ov106_0229cd60(void *ptr, unsigned char b);
extern void func_ov106_0229d73c(void *ptr);
extern void func_ov106_0229cde4(void *ptr);
extern int func_ov002_02208e28(char *);
extern int func_0206fe54(void);
extern void func_ov106_0229ca90(char *);
extern int func_ov002_0220909c(void *p);
extern void func_ov002_022096d8(char *p, int v);
extern int func_ov002_02207d24(char *p, int v);
extern int func_0208e4bc(void *p);
extern void func_ov106_0229ca5c(void *p);
extern int func_ov002_02208e18(void *);
extern void func_ov106_0229c910(void *);
extern int func_ov002_0220b8ac(void *p, int x);
extern void func_0208e5cc(void *p);
extern int func_ov002_0220b804(void *p);
extern int func_ov002_02207f3c(void *p, int n);
extern unsigned int func_ov002_02207f60(void *p);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern int func_ov002_0220a99c(void *p);
extern void func_ov002_0220a6b8(void *p);
extern int func_ov002_02207f48(struct UnkStruct_0229dc80 *p, int flag);
extern void func_ov106_0229d6a4(struct UnkStruct_0229dc80 *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_0206f56c(void);
extern int func_ov002_02208054(UnkStruct_0229dc04 *obj, int x);
extern int func_ov002_0220a784(void *ptr, int x);
extern void func_ov106_0229d3bc(UnkStruct_0229dc04 *obj);
extern void func_ov106_0229d6c4(UnkStruct_0229dc04 *obj);
extern void func_ov106_0229d3e8(UnkStruct_0229dc04 *obj);

void func_ov106_0229df98(void *p)
{
    if (func_0208e484((char *) p + 0x22a0) == 0) {
        return;
    }
    if (*(unsigned char *) ((char *) p + 0xb8) == 0x1f) {
        func_ov106_0229c378(p);
    } else {
        func_ov106_0229c9fc(p);
    }
}

void func_ov106_0229df70(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x22a0)) {
        func_ov106_0229ca3c(arg0);
        func_ov002_02208098((void *) (arg0), 7);
    }
}

void func_ov106_0229df40(unsigned char *self)
{
    if (func_ov002_02209f9c(self + 0x22a0) != 0) {
        func_ov106_0229d57c(self, self[0xb8]);
        func_ov002_02208098((void *) (self), 0x11);
    }
}

void func_ov106_0229df14(unsigned char *p)
{
    if (func_0208e484((void *) (p + 0x22a0)) != 0) {
        func_ov002_02208098((void *) (p), p[0xbb]);
    }
    func_ov106_0229ce0c(p);
}

void func_ov106_0229dec0(unsigned char *arg)
{
    unsigned char ba;
    unsigned char b8;

    if (func_ov002_02209f9c(arg + 0x22a0) == 0) {
        ba = arg[0xba];
        b8 = arg[0xb8];
        if (b8 == ba) {
            func_ov106_0229d29c(arg, ba);
            func_ov106_0229cea8(arg);
            func_ov002_02208098((void *) (arg), 7);
            func_ov094_022999d8();
        } else {
            func_ov106_0229d518(arg, ba, 4);
        }
    } else {
        func_ov106_0229ce0c((const void *) arg);
    }
}

void func_ov106_0229de78(void *self)
{
    if (func_ov002_02209f70((char *) self + 0x22a0) == 0) {
        func_ov106_0229cd20(self, ((unsigned char *) self)[0xba]);
        func_ov106_0229c354(self, 0x40);
        func_ov002_02208098((void *) (self), 0x14);
        func_ov106_0229cea8(self);
    } else {
        func_ov002_02208098((void *) (self), 7);
    }
}

void func_ov106_0229de28(UnkStruct_0229de28 *self)
{
    if (func_0208e484(&self->unk_22A0) != 0) {
        func_ov002_02208098((void *) (self), self->flag);
    }
    if (func_ov002_02209f9c(&self->unk_22A0) != 0) {
        if (func_ov106_0229c364(self, 0x40) != 0) {
            ((void) (func_ov106_0229c344(self, 0x40)), func_ov094_022999c0());
        }
        func_ov106_0229ce0c((const void *) self);
    }
}

void func_ov106_0229ddf0(void *r4)
{
    if (func_ov002_02209d8c((char *) r4 + 0x2288)) {
        func_ov106_0229cd60(r4, *(unsigned char *) ((char *) r4 + 0xB7));
        ((void) (func_ov106_0229d73c(r4)), func_ov094_022999d8());
    } else {
        func_ov106_0229cde4(r4);
    }
}

void func_ov106_0229ddb4(char *param)
{
    if (func_ov002_02208e28(param + 0x2304)) {
        if (func_0206fe54()) {
            func_ov106_0229ca90(param);
            func_ov002_02208098((void *) (param), 0xb);
        } else {
            func_ov002_02208098((void *) (param), 6);
        }
    }
}

void func_ov106_0229dd64(void *s)
{
    unsigned int self = (unsigned int) s;

    if (func_ov002_0220909c((void *) (self + 0x2304)) != 0) {
        func_ov002_022096d8((char *) (self + 0x2304), 0);
        func_ov002_02207d24((char *) (self + 0x21b8), 1);
        if (func_0208e4bc((void *) (self + 0x22a0)) != 0) {
            func_ov106_0229ca5c((void *) self);
        }
        func_ov002_02208098((void *) ((void *) self), 0x18);
    }
}

void func_ov106_0229dd44(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x2304) != 0) {
        func_ov106_0229c910(self);
    }
}

void func_ov106_0229dd10(St *self)
{
    if (func_ov002_0220b8ac(&self->field_at_26f8, 1)) {
        func_ov002_02208098((void *) (self), self->byte_at_bb);
        func_0208e5cc(&self->field_at_22a0);
    }
}

void func_ov106_0229dcb0(UnkStruct_0229dcb0 *self)
{
    int temp = func_ov002_0220b804(&self->unk_26F8);
    temp &= func_ov002_02207f3c(self, -1);
    self->unk_A0 = func_ov002_02207f60(self);
    if (temp != 0) {
        func_ov002_02208098((void *) (self), 0x1b);
        func_ov002_02207eb4(self, 0, 0);
        func_ov002_0220a99c(&self->unk_3FB4);
        func_ov002_0220a6b8(&self->unk_3FB4);
    }
}

void func_ov106_0229dc80(struct UnkStruct_0229dc80 *self)
{
    int result1;
    int result2;
    result1 = func_ov002_02207f48(self, -1);
    result2 = (int) func_ov002_02207f60((void *) self);
    self->unk_A0 = result2;
    if (result1 != 0) {
        func_ov106_0229d6a4(self);
    }
}

void func_ov106_0229dc04(UnkStruct_0229dc04 *obj)
{
    int v;

    if (func_0206f56c()) {
        func_ov106_0229d3bc(obj);
    }
    if (func_ov002_02208054(obj, 1)) {
        func_ov106_0229d6c4(obj);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (v != 0) {
        if (func_ov002_0220a784(&obj->unk_3FB4, 3)) {
            func_ov106_0229d3e8(obj);
            return;
        }
        if (func_ov002_0220a784(&obj->unk_3FB4, 4)) {
            func_ov106_0229d3bc(obj);
        }
    }
}
