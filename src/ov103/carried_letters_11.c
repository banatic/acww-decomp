/* carried_letters_11: 14 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229dd40 @ 0x0229dd40, 0x4 bytes, Thumb
 * func_ov103_0229dd3c @ 0x0229dd3c, 0x4 bytes, Thumb
 * func_ov103_0229dd2c @ 0x0229dd2c, 0x10 bytes, Thumb
 * func_ov103_0229dd10 @ 0x0229dd10, 0x1c bytes, Thumb
 * func_ov103_0229dc9c @ 0x0229dc9c, 0x74 bytes, Thumb
 * func_ov103_0229dc60 @ 0x0229dc60, 0x3c bytes, Thumb
 * func_ov103_0229dbec @ 0x0229dbec, 0x74 bytes, Thumb
 * func_ov103_0229db7c @ 0x0229db7c, 0x70 bytes, Thumb
 * func_ov103_0229daf4 @ 0x0229daf4, 0x88 bytes, Thumb
 * func_ov103_0229daa4 @ 0x0229daa4, 0x50 bytes, Thumb
 * func_ov103_0229da68 @ 0x0229da68, 0x3c bytes, Thumb
 * func_ov103_0229da20 @ 0x0229da20, 0x48 bytes, Thumb
 * func_ov103_0229d99c @ 0x0229d99c, 0x84 bytes, Thumb
 * func_ov103_0229d960 @ 0x0229d960, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_00[0x2b8c];
    int unk_2B8C;
} UnkStruct_0229db7c;

extern void func_020ee470(void *parameter0);
extern void func_ov103_0229d8b4(void);
extern void func_ov103_0229d8a0(int a);
extern void func_ov002_02208090(int a, int b);
extern int func_ov103_0229d890(char *self);
extern void func_ov094_0229ad20(char *ptr);
extern void func_ov094_0229b2b0(char *ptr);
extern void func_ov103_0229cc70(char *self);
extern void func_ov002_02207f20(char *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov103_0229c2e4(char *self, int a);
extern int func_ov002_02207f60(char *self);
extern void func_ov103_0229cfa0(int a);
extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(int a, unsigned char value);
extern void func_ov002_02207e80(int a, int b, int c, int d);
extern int func_ov002_02207d24(void *addr, int value);
extern void func_ov103_0229c7ec(void *ptr);
extern int func_ov103_0229c2f4(void *ptr, int param);
extern int func_020ee45c(void *ptr);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *ptr, int a, int b, int c, int d);
extern int func_ov002_02207f3c(UnkStruct_0229db7c *, int);
extern void func_020027f0(int);
extern void func_ov103_0229c2d4(UnkStruct_0229db7c *, int);
extern int func_ov103_0229cce8(unsigned char *, unsigned char);
extern void func_020664a8(int);
extern void func_0206e230(unsigned char *, int, int, int, int);
extern void func_ov002_0220b53c(unsigned char *, int);
extern int func_0206fe60(void);
extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);
extern void func_0206e2ec(void *p, int a);
extern void func_ov103_0229ce0c(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);
extern void func_0206e2e4(void *);

void func_ov103_0229daf4(unsigned char *self);

int func_ov103_0229dd40(void)
{
    return 1;
}

int func_ov103_0229dd3c(void)
{
    return 1;
}

int func_ov103_0229dd2c(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov103_0229dd10(int a)
{
    func_ov103_0229d8b4();
    func_ov103_0229d8a0(a);
    func_ov002_02208090(a, 1);
}

void func_ov103_0229dc9c(char *self)
{
    func_ov103_0229d890(self);
    func_ov094_0229ad20(self + 0xcc);
    func_ov094_0229b2b0(self + 0xb2c);
    func_ov103_0229cc70(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80((int) self, 6, 0, 0);
    func_ov002_02208090((int) self, 2);
    func_ov103_0229c2e4(self, 1);
    func_ov103_0229c2e4(self, 2);
    *(unsigned int *) (self + 0x2b8c) = func_ov002_02207f60(self);
}

void func_ov103_0229dc60(int a)
{
    if (func_ov002_02207f48(a, 0)) {
        func_ov002_022080a0(a, 2);
        func_ov103_0229cfa0(a);
    }
    func_ov002_02207e80(a, 6, 0, 0);
    *(int *) ((char *) a + 0x2b8c) = func_ov002_02207f60((char *) a);
}

void func_ov103_0229dbec(void *ptr)
{
    func_ov002_02207d24((char *) ptr + 0x218c, 1);
    func_ov103_0229c7ec(ptr);
    if (func_ov103_0229c2f4(ptr, 0x100) == 0) {
        func_ov092_02299324(func_020ee45c(ptr), 0x44, 1);
    }
    func_ov002_02207f04(ptr, 8, 0, 0, 0x30);
    func_ov002_02207e80((int) ptr, 6, 0, 0);
    func_ov002_02208090((int) ptr, 4);
    *((int *) ((char *) ptr + 0x2b8c)) = func_ov002_02207f60((char *) ptr);
}

void func_ov103_0229db7c(UnkStruct_0229db7c *obj)
{
    if (func_ov002_02207f3c(obj, 0) != 0) {
        func_020027f0(6);
        func_ov103_0229c2d4(obj, 2);
        if (func_ov103_0229c2f4((void *) obj, 0x100) != 0) {
            func_ov002_02208090((int) obj, 5);
            func_ov103_0229daf4((unsigned char *) obj);
        } else {
            func_ov103_0229c2d4(obj, 1);
            func_ov002_022080a0((int) obj, 5);
        }
    } else {
        func_ov002_02207e80((int) obj, 6, 0, 0);
    }
    obj->unk_2B8C = func_ov002_02207f60((char *) obj);
}

void func_ov103_0229daf4(unsigned char *self)
{
    int ret;

    ret = func_ov103_0229cce8(self, self[0x2da5]);
    func_020664a8(ret);
    func_0206e230(self + 0x27e8, ret, 3, 4, 1);
    func_ov002_02207f20((char *) self, 3, 0, 0, 0x30);
    func_02002708(3);
    func_ov002_02207e80((int) self, 3, 0, 0);
    func_02002708(4);
    func_ov002_02207e80((int) self, 4, 0, 0);
    func_ov002_02208090((int) self, 6);
    func_ov002_0220b53c(self + 0x2b10, 0x88);
    func_ov103_0229c2e4((char *) self, 0x80);
}

void func_ov103_0229daa4(int p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        if (func_0206fe60()) {
            func_ov002_02208098(p, 3);
        } else {
            func_ov002_02208098(p, 7);
        }
    } else {
        func_ov002_02207e80(p, 3, 0, 0);
        func_ov002_02207e80(p, 4, 0, 0);
    }
}

void func_ov103_0229da68(int r0)
{
    int sp[2];
    sp[0] = 0x30;
    func_ov002_02207f04((void *) r0, 3, 0, 0, sp[0]);
    func_ov002_02207e80(r0, 3, 0, 0);
    func_ov002_02207e80(r0, 4, 0, 0);
    func_ov002_02208090(r0, 8);
}

void func_ov103_0229da20(int arg0)
{
    extern void func_020027f0(int);
    extern void func_ov103_0229dd10(int);
    extern void func_ov002_02207e80(int, int, int, int);

    if (func_ov002_02207f3c((UnkStruct_0229db7c *) arg0, 0) != 0) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov103_0229c2d4((UnkStruct_0229db7c *) arg0, 0x80);
        func_ov103_0229dd10(arg0);
    } else {
        func_ov002_02207e80(arg0, 3, 0, 0);
        func_ov002_02207e80(arg0, 4, 0, 0);
    }
}

void func_ov103_0229d99c(void *self)
{
    *(int *) ((char *) self + 0x2b88) = 0;
    func_ov094_0229af40((char *) self + 0xcc, 2);
    func_ov094_0229bbd8((char *) self + 0xb2c, 2);
    func_ov094_0229a2b0((char *) self + 0xb54, 6);
    *(char *) ((char *) self + 0x2da2) = 0x15;
    func_ov002_02209e18((char *) self + 0x225c);
    *(char *) ((char *) self + 0x2da0) = 0;
    *(char *) ((char *) self + 0x2da4) = 0xb;
    func_ov002_02209984((char *) self + 0x22d8, 3, 1, 0);
    func_0206e2ec((char *) self + 0x27e8, 3);
}

void func_ov103_0229d960(void *self)
{
    func_ov103_0229ce0c(self);
    func_ov094_0229a038((char *) self + 0xb54);
    func_ov094_0229af18((char *) self + 0xcc);
    func_ov002_02209178((char *) self + 0x22d8);
    func_0206e2e4((char *) self + 0x27e8);
}
