/* pockets_view_5: 10 functions, module ov099
 * mwccarm 1.2/base -O4,s
 * func_ov099_0229dbc4 @ 0x0229dbc4, 0x4 bytes, Thumb
 * func_ov099_0229dbc0 @ 0x0229dbc0, 0x4 bytes, Thumb
 * func_ov099_0229dbb0 @ 0x0229dbb0, 0x10 bytes, Thumb
 * func_ov099_0229db94 @ 0x0229db94, 0x1c bytes, Thumb
 * func_ov099_0229db24 @ 0x0229db24, 0x70 bytes, Thumb
 * func_ov099_0229dae8 @ 0x0229dae8, 0x3c bytes, Thumb
 * func_ov099_0229da84 @ 0x0229da84, 0x64 bytes, Thumb
 * func_ov099_0229da34 @ 0x0229da34, 0x50 bytes, Thumb
 * func_ov099_0229d994 @ 0x0229d994, 0xa0 bytes, Thumb
 * func_ov099_0229d964 @ 0x0229d964, 0x30 bytes, Thumb
 */

struct UnkStruct_0229db24 {
    char pad_00[0xcc];
    char sub1;
    char pad_CD[0xb2c - 0xcc - 1];
    char sub2;
    char pad_B2D[0x27ec - 0xb2c - 1];
    unsigned int unk_27EC;
};

typedef struct StructName {
    char pad_00[0x27ec];
    int unk_27EC;
} StructName;

struct UnkStruct_0229da34 {
    char pad_00[0x27ec];
    unsigned int unk_27EC;
};

extern void func_020ee470(void *parameter0);
extern void func_ov099_0229d8b8(void);
extern void func_ov099_0229d8a4(void *self);
extern void func_ov002_02208090(void *self, int state);
extern int func_ov099_0229d894(void *);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov099_0229c29c(void *, int);
extern int func_ov002_02207f48(StructName *p, int a);
extern unsigned char *func_ov002_022080a0(StructName *p, unsigned char value);
extern void func_ov099_0229d0f0(StructName *p);
extern int func_ov002_02207d24(void *addr, int value);
extern void func_ov099_0229c754(void *obj);
extern int func_020ee45c(void *obj);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *obj, int a, int b, int c, int d);
extern int func_ov002_02207f60(void *obj);
extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern void func_ov099_0229c28c(void *p, int n);
extern void func_ov094_0229af40(void *, int);
extern void func_ov094_0229bbd8(void *, int);
extern void func_ov094_0229a2b0(void *, int);
extern void func_ov002_02209e18(void *);
extern void func_ov002_02209984(void *, unsigned char, int, void *);
extern void func_0209a088(void *, int, int);
extern void func_ov099_0229cf3c(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);

int func_ov099_0229dbc4(void)
{
    return 1;
}

int func_ov099_0229dbc0(void)
{
    return 1;
}

int func_ov099_0229dbb0(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov099_0229db94(void *arg0)

{
    func_ov099_0229d8b8();
    func_ov099_0229d8a4(arg0);
    func_ov002_02208090(arg0, 1);
    return;
}

void func_ov099_0229db24(struct UnkStruct_0229db24 *self)
{
    func_ov099_0229d894(self);
    func_ov094_0229ad20(&self->sub1);
    func_ov094_0229b2b0(&self->sub2);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 2);
    func_ov099_0229c29c(self, 1);
    func_ov099_0229c29c(self, 2);
    self->unk_27EC = (unsigned int) func_ov002_02207f60(self);
}

void func_ov099_0229dae8(StructName *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov099_0229d0f0(p);
    }
    func_ov002_02207e80((void *) p, 6, 0, 0);
    p->unk_27EC = func_ov002_02207f60((void *) p);
}

void func_ov099_0229da84(void *obj)
{
    func_ov002_02207d24((char *) obj + 0x218C, 1);
    func_ov099_0229c754(obj);
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 8, 0, 0, 0x30);
    func_ov002_02207e80(obj, 6, 0, 0);
    func_ov002_02208090(obj, 4);
    *(int *) ((char *) obj + 0x27EC) = func_ov002_02207f60(obj);
}

void func_ov099_0229da34(struct UnkStruct_0229da34 *this)
{
    if (func_ov002_02207f3c(this, 0) != 0) {
        func_020027f0(6);
        func_ov002_022080a0((StructName *) this, 5);
        func_ov099_0229c28c(this, 1);
        func_ov099_0229c28c(this, 2);
    } else {
        func_ov002_02207e80(this, 6, 0, 0);
    }
    this->unk_27EC = func_ov002_02207f60(this);
}

void func_ov099_0229d994(unsigned char *self)
{
    unsigned short buf[2];
    *((unsigned int *) (self + 0x27e8)) = 0;
    func_ov094_0229af40(self + 0xcc, 2);
    func_ov094_0229bbd8(self + 0xb2c, 2);
    func_ov094_0229a2b0(self + 0xb54, 6);
    *((unsigned char *) (self + 0x2905)) = 0x1d;
    func_ov002_02209e18(self + 0x225c);
    *((unsigned char *) (self + 0x2903)) = 0;
    *((unsigned char *) (self + 0x2907)) = 0;
    func_ov002_02209984(self + 0x22d8, 3, 1, 0);
    buf[0] = 0x11a9;
    func_0209a088(buf, 1, 0);
    buf[1] = 0x1548;
    func_0209a088(&buf[1], 0, 2);
}

void func_ov099_0229d964(void *this_ptr)
{
    func_ov099_0229cf3c(this_ptr);
    func_ov094_0229a038((char *) this_ptr + 0xb54);
    func_ov094_0229af18((char *) this_ptr + 0xcc);
    func_ov002_02209178((char *) this_ptr + 0x22d8);
}
