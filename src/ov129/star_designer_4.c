/* star_designer_4: 19 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229d764 @ 0x0229d764, 0x1c bytes, Thumb
 * func_ov129_0229d760 @ 0x0229d760, 0x4 bytes, Thumb
 * func_ov129_0229d75c @ 0x0229d75c, 0x4 bytes, Thumb
 * func_ov129_0229d74c @ 0x0229d74c, 0x10 bytes, Thumb
 * func_ov129_0229d6e4 @ 0x0229d6e4, 0x66 bytes, Thumb
 * func_ov129_0229d69c @ 0x0229d69c, 0x46 bytes, Thumb
 * func_ov129_0229d654 @ 0x0229d654, 0x46 bytes, Thumb
 * func_ov129_0229d618 @ 0x0229d618, 0x3c bytes, Thumb
 * func_ov129_0229d5ec @ 0x0229d5ec, 0x2a bytes, Thumb
 * func_ov129_0229d5a4 @ 0x0229d5a4, 0x46 bytes, Thumb
 * func_ov129_0229d588 @ 0x0229d588, 0x1a bytes, Thumb
 * func_ov129_0229d554 @ 0x0229d554, 0x32 bytes, Thumb
 * func_ov129_0229d500 @ 0x0229d500, 0x54 bytes, Thumb
 * func_ov129_0229d4d4 @ 0x0229d4d4, 0x2c bytes, Thumb
 * func_ov129_0229d4b8 @ 0x0229d4b8, 0x1a bytes, Thumb
 * func_ov129_0229d490 @ 0x0229d490, 0x26 bytes, Thumb
 * func_ov129_0229d440 @ 0x0229d440, 0x50 bytes, Thumb
 * func_ov129_0229d3f8 @ 0x0229d3f8, 0x48 bytes, Thumb
 * func_ov129_0229d3e0 @ 0x0229d3e0, 0x16 bytes, Thumb
 */

struct func_ov129_0229d5ec_obj {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
};

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
} UnkStruct_0229d554;

struct obj_struct {
    char pad_00[0x1d4];
    int unk_1D4;
};

struct UnkStruct_0229d4d4 {
    unsigned char pad_00[0xa0];
    int unk_A0;
};

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
} UnkStruct_0229d490;

extern void func_ov129_0229d24c(void *);
extern void func_ov129_0229d780(void *);
extern void func_ov129_0229d244(void *);
extern void func_020ee470(void *argument0);
extern void func_ov129_0229d180(void);
extern void func_ov129_0229d110(void *);
extern void func_ov129_0229bf10(void *);
extern void func_ov129_0229b7dc(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02001d60(int, int);
extern void func_02002708(int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov129_0229c820(void *p);
extern void func_ov129_0229bee4(void *p, int x);
extern void func_02001b6c(int x);
extern int func_020ee45c(int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(int, int, int, int, int);
extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int n);
extern void func_ov002_02207e80(struct func_ov129_0229d5ec_obj *, int, int, int);
extern void func_02001b7c(int);
extern void func_02002808(int, int, int, int, int);
extern void func_ov002_02207e9c(void *, int, int);
extern void func_ov002_02207eb4(void *a, int b, int c);
extern void func_ov002_0220a63c(void *a, int b);
extern int func_ov129_0229b7ec(void *a, int b);
extern int func_ov002_0220a9e4(void *a, int b);
extern void func_ov129_0229b7cc(void *a, int b);
extern int func_ov129_0229d360(void *a);
extern int func_ov002_02207f60(void *a);
extern int func_ov002_0220abbc(void *);
extern void func_ov002_0220a658(void *, int);
extern void func_ov129_0229c3f4(int arg);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov129_0229d5ec(struct func_ov129_0229d5ec_obj *self);
void func_ov129_0229d5a4(int param);
void func_ov129_0229d500(struct obj_struct *obj);
void func_ov129_0229d440(unsigned char *obj);

int func_ov129_0229d764(void *p)
{
    func_ov129_0229d24c(p);
    func_ov129_0229d780(p);
    func_ov129_0229d244(p);
    return 1;
}

int func_ov129_0229d760(void)
{
    return 1;
}

int func_ov129_0229d75c(void)
{
    return 1;
}

int func_ov129_0229d74c(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov129_0229d6e4(void *param)
{
    func_ov129_0229d180();
    func_ov129_0229d110(param);
    func_ov129_0229bf10(param);
    func_ov002_02207f20(param, 9, 4, 0, 0x30);
    func_02001d60(0x1e, 1);
    func_ov129_0229d5a4((int) param);
    func_02002708(3);
    func_02002708(6);
    func_ov129_0229b7dc(param, 1);
    func_ov129_0229b7dc(param, 8);
    func_ov129_0229d5ec((struct func_ov129_0229d5ec_obj *) param);
    func_ov002_02208090(param, 1);
}

void func_ov129_0229d69c(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov129_0229c820(p);
        func_ov129_0229b7dc(p, 16);
        func_ov129_0229bee4(p, 1);
        func_02001b6c(2);
    } else {
        func_ov129_0229d5a4((int) p);
    }
    func_ov129_0229d5ec((struct func_ov129_0229d5ec_obj *) p);
}

void func_ov129_0229d654(int a0)
{
    func_ov092_02299324(func_020ee45c(a0), 0x44, 1);
    func_ov002_02207f04(a0, 9, 0, 0, 48);
    func_02001d60(30, 1);
    func_ov129_0229d5a4(a0);
    func_ov129_0229d5ec((struct func_ov129_0229d5ec_obj *) a0);
    func_ov002_02208090((void *) a0, 3);
}

void func_ov129_0229d618(void *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(3);
        func_020027f0(6);
        func_02001b6c(2);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov129_0229d5a4((int) param);
        func_ov129_0229d5ec((struct func_ov129_0229d5ec_obj *) param);
    }
}

void func_ov129_0229d5ec(struct func_ov129_0229d5ec_obj *self)
{
    func_ov002_02207e80(self, 6, 0, 0);
    self->unk_9C = func_ov002_02207f60((void *) self);
    self->unk_A0 = func_ov002_02207f60((void *) self);
}

void func_ov129_0229d5a4(int param)
{
    int a, b;

    a = func_ov002_02207f60((void *) param) - 0x40;
    if (a < 0) {
        a = 0;
    }

    b = func_ov002_02207f60((void *) param) - 0x30;

    if (b <= 0) {
        func_02001b6c(2);
    } else {
        func_02001b7c(2);
        func_02002808(3, 0, a, 0xff, b);
    }
}

void func_ov129_0229d588(void *p)
{
    int a = 0;
    func_ov002_02207e9c(p, a, a);
    func_ov002_02208090(p, 5);
}

void func_ov129_0229d554(UnkStruct_0229d554 *arg)
{
    if (func_ov002_02207f3c((void *) arg, -1)) {
        func_ov129_0229d500((struct obj_struct *) arg);
    }
    arg->unk_A0 = func_ov002_02207f60((void *) arg);
    arg->unk_9C = func_ov002_02207f60((void *) arg);
}

void func_ov129_0229d500(struct obj_struct *obj)
{
    func_ov002_02207eb4(obj, 0, 0);
    func_ov002_0220a63c(&obj->unk_1D4, 6);
    if (func_ov129_0229b7ec(obj, 4)) {
        func_ov002_0220a9e4(&obj->unk_1D4, 0x87);
    } else {
        func_ov002_0220a9e4(&obj->unk_1D4, 0x22);
    }
    func_ov129_0229b7cc(obj, 1);
    func_ov002_02208090(obj, 7);
}

void func_ov129_0229d4d4(struct UnkStruct_0229d4d4 *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0((void *) (arg), 2);
        func_ov129_0229d360(arg);
    }
    arg->unk_A0 = func_ov002_02207f60(arg);
}

void func_ov129_0229d4b8(int r0)
{
    int r4 = r0;
    func_ov002_02207e9c((void *) r4, 0, 0);
    func_ov002_02208090((void *) r4, 9);
}

void func_ov129_0229d490(UnkStruct_0229d490 *s)
{
    if (func_ov002_02207f3c((void *) s, -1) != 0) {
        func_ov129_0229d440((unsigned char *) s);
    }
    s->unk_A0 = func_ov002_02207f60((void *) s);
}

void func_ov129_0229d440(unsigned char *obj)
{
    func_ov002_02207eb4(obj, 0, 0);
    func_ov002_0220abbc(obj + 0x1d4);
    if (obj[0xb1] == 2) {
        func_ov002_0220a63c(obj + 0x1d4, 6);
    } else {
        func_ov002_0220a658(obj + 0x1d4, 6);
    }
    func_ov002_02208090(obj, 11);
    func_ov129_0229b7dc(obj, 1);
}

void func_ov129_0229d3f8(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov129_0229c820(p);
        func_ov129_0229b7dc(p, 0x10);
        func_ov129_0229bee4(p, 1);
    }
    *(int *) ((char *) p + 0xA0) = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x9C) = func_ov002_02207f60(p);
}

unsigned char *func_ov129_0229d3e0(int arg)
{
    func_ov129_0229c3f4(arg);
    return func_ov002_02208098((void *) (arg), 0xB);
}
