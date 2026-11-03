/* song_pockets_4: 11 functions, module ov109
 * mwccarm 1.2/base -O4,s
 * func_ov109_0229d764 @ 0x0229d764, 0x50 bytes, Thumb
 * func_ov109_0229d760 @ 0x0229d760, 0x4 bytes, Thumb
 * func_ov109_0229d75c @ 0x0229d75c, 0x4 bytes, Thumb
 * func_ov109_0229d74c @ 0x0229d74c, 0x10 bytes, Thumb
 * func_ov109_0229d730 @ 0x0229d730, 0x1c bytes, Thumb
 * func_ov109_0229d6a0 @ 0x0229d6a0, 0x90 bytes, Thumb
 * func_ov109_0229d660 @ 0x0229d660, 0x40 bytes, Thumb
 * func_ov109_0229d5e0 @ 0x0229d5e0, 0x80 bytes, Thumb
 * func_ov109_0229d590 @ 0x0229d590, 0x50 bytes, Thumb
 * func_ov109_0229d514 @ 0x0229d514, 0x7c bytes, Thumb
 * func_ov109_0229d4d8 @ 0x0229d4d8, 0x3c bytes, Thumb
 */

typedef struct UnkStruct_0229d660 {
    unsigned char pad_00[0x29b8];
    unsigned int unk_29B8;
} UnkStruct_0229d660;

typedef struct {
    char pad_00[0x29b8];
    int unk_29B8;
} UnkStruct_0229d590;

struct UnkStruct_0229d514 {
    unsigned char pad_00[0x29b4];
    unsigned int unk_29B4;
    unsigned char pad_29B8[0x29cf - 0x29b8];
    unsigned char unk_29CF;
    unsigned char pad_29D0[0x29d1 - 0x29d0];
    unsigned char unk_29D1;
    unsigned char pad_29D2[0x29d3 - 0x29d2];
    unsigned char unk_29D3;
    unsigned char pad_29D4[0x29d9 - 0x29d4];
    unsigned char unk_29D9;
};

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern void func_ov109_0229c4cc(void *p);
extern void func_ov109_0229c498(void *p);
extern void func_ov109_0229c29c(void *p, int);
extern void func_ov109_0229d4bc(void *p);
extern void func_ov109_0229d7b4(void *p);
extern void func_ov109_0229d4b4(void *p);
extern void func_020ee470(void *parameter0);
extern void func_ov109_0229d420(void);
extern void func_ov109_0229d40c(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov109_0229d3e8(void *obj);
extern int func_ov002_0220ab84(void *ptr, int a);
extern void func_ov094_0229ad20(void *ptr);
extern void func_ov109_0229cb10(void *obj);
extern void func_ov094_0229b2b0(void *ptr);
extern void func_ov094_0229b794(void *ptr, int a);
extern void func_ov002_02207f20(void *obj, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(void *obj, int a, int b, int c);
extern int func_ov002_02207f60(void *obj);
extern int func_ov002_02207f48(UnkStruct_0229d660 *self, int a);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229d660 *self, unsigned char value);
extern void func_ov109_0229cd9c(UnkStruct_0229d660 *self);
extern int func_ov002_02207d24(void *ptr, int a);
extern void func_ov109_0229c828(void *ptr);
extern int func_020ee45c(void *ptr);
extern int func_ov109_0229c2ac(void *ptr, int a);
extern void func_ov092_02299324(void *ptr, int a, int b);
extern void func_ov002_02207f04(void *ptr, int a, int b, int c, int d);
extern int func_ov002_02207f3c(void *p, int a);
extern void func_020027f0(int a);
extern void func_ov109_0229c28c(void *p, int a);
extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);
extern void func_ov109_0229ccc0(void *arg0);
extern void func_ov094_0229a038(void *p);
extern void func_ov094_0229af18(void *p);
extern void func_ov002_02209178(void *p);
extern void func_ov002_0220af74(void *p);

int func_ov109_0229d764(void *self)
{
    func_0206f58c();
    if (func_0206f56c() != 0) {
        unsigned char b = ((unsigned char *) self)[0x8d];
        if (b == 0 || b == 1 || b == 5) {
            func_ov109_0229c4cc(self);
            func_ov109_0229c498(self);
            func_ov109_0229c29c(self, 0x40);
        }
    }
    func_ov109_0229d4bc(self);
    func_ov109_0229d7b4(self);
    func_ov109_0229d4b4(self);
    return 1;
}

int func_ov109_0229d760(void)
{
    return 1;
}

int func_ov109_0229d75c(void)
{
    return 1;
}

int func_ov109_0229d74c(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov109_0229d730(void *arg)
{
    func_ov109_0229d420();
    func_ov109_0229d40c(arg);
    func_ov002_02208090(arg, 1);
}

void func_ov109_0229d6a0(void *obj)
{
    int zero = 0;
    func_ov109_0229d3e8(obj);
    func_ov002_0220ab84((char *) obj + 0x27e8, 0x65);
    func_ov094_0229ad20((char *) obj + 0xcc);
    func_ov109_0229cb10(obj);
    func_ov094_0229b2b0((char *) obj + 0xb2c);
    func_ov094_0229b794((char *) obj + 0xb2c, 0xf);
    func_ov002_02207f20(obj, 8, zero, zero, 0x30);
    func_02002708(6);
    func_ov002_02207e80(obj, 6, 0, -16);
    func_ov002_02208090(obj, 2);
    func_ov109_0229c29c(obj, 1);
    func_ov109_0229c29c(obj, 2);
    *(int *) ((char *) obj + 0x29b8) = func_ov002_02207f60(obj);
}

void func_ov109_0229d660(UnkStruct_0229d660 *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0(self, 2);
        func_ov109_0229cd9c(self);
    }
    func_ov002_02207e80((void *) self, 6, 0, ~0xf);
    self->unk_29B8 = (unsigned int) func_ov002_02207f60((void *) self);
}

void func_ov109_0229d5e0(char *this_)
{
    int ret;

    func_ov002_02207d24(this_ + 0x218c, 1);
    func_ov109_0229c828(this_);
    ret = func_020ee45c(this_);
    if (func_ov109_0229c2ac(this_, 0x40)) {
        func_ov092_02299324((void *) ret, 0x44, 1);
    } else {
        func_ov092_02299324((void *) ret, 0x40, 1);
    }
    func_ov002_02207f04(this_, 8, 0, 0, 48);
    func_ov002_02207e80(this_, 6, 0, -16);
    func_ov002_02208090(this_, 4);
    *(int *) (this_ + 0x29b8) = func_ov002_02207f60(this_);
}

void func_ov109_0229d590(UnkStruct_0229d590 *p)
{
    if (func_ov002_02207f3c(p, 0) != 0) {
        func_020027f0(6);
        func_ov002_022080a0((UnkStruct_0229d660 *) p, 5);
        func_ov109_0229c28c(p, 1);
        func_ov109_0229c28c(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, -16);
    }
    p->unk_29B8 = func_ov002_02207f60(p);
}

void func_ov109_0229d514(struct UnkStruct_0229d514 *self)
{
    self->unk_29B4 = 0;
    func_ov094_0229af40((char *) self + 0xcc, 2);
    func_ov094_0229bbd8((char *) self + 0xb2c, 2);
    func_ov094_0229a2b0((char *) self + 0xb54, 6);
    self->unk_29D1 = 0x10;
    func_ov002_02209e18((char *) self + 0x225c);
    self->unk_29CF = 0;
    self->unk_29D3 = 0;
    func_ov002_02209984((char *) self + 0x22d8, 3, 1, 0);
    self->unk_29D9 = 0;
}

void func_ov109_0229d4d8(void *self)
{
    func_ov109_0229ccc0((void *) self);
    func_ov094_0229a038((char *) self + 0xb54);
    func_ov094_0229af18((char *) self + 0xcc);
    func_ov002_02209178((char *) self + 0x22d8);
    func_ov002_0220af74((char *) self + 0x27e8);
}
