/* donation_list_states_3: 10 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_0229aa44 @ 0x0229aa44, 0x4 bytes, Thumb
 * func_ov145_0229aa40 @ 0x0229aa40, 0x4 bytes, Thumb
 * func_ov145_0229aa30 @ 0x0229aa30, 0x10 bytes, Thumb
 * func_ov145_0229a9b8 @ 0x0229a9b8, 0x78 bytes, Thumb
 * func_ov145_0229a990 @ 0x0229a990, 0x28 bytes, Thumb
 * func_ov145_0229a958 @ 0x0229a958, 0x38 bytes, Thumb
 * func_ov145_0229a928 @ 0x0229a928, 0x30 bytes, Thumb
 * func_ov145_0229a8e8 @ 0x0229a8e8, 0x3e bytes, Thumb
 * func_ov145_0229a884 @ 0x0229a884, 0x64 bytes, Thumb
 * func_ov145_0229a844 @ 0x0229a844, 0x40 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned char unk_C0;
    unsigned char unk_C1;
    unsigned char pad_C2[0xb2];
    unsigned char unk_174;
} UnkStruct_0229a9b8;

extern void func_020ee470(void *argument0);
extern void func_ov145_0229a778(void);
extern void func_ov145_0229a6c8(void *);
extern void func_ov145_0229996c(void *, int);
extern void func_ov145_0229a678(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov145_02299658(void *, int);
extern int func_ov002_02207f48(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov145_0229a310(void *p);
extern int func_020ee45c(void *p);
extern void func_ov092_02299324(int x, int a, int b);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern void func_ov002_02207e80(void *ptr, int a, int b, int c);
extern int func_ov002_02207f60(void *ptr);
extern void func_ov145_0229a134(void *ptr);
extern void func_ov145_0229a034(void *);
extern void func_ov145_0229a010(void *);
extern void func_ov145_02299fec(void *);
extern void func_ov145_02299fc8(void *);
extern void func_ov002_0220a580(void *);
extern void func_ov145_02299da4(void *unused0);
extern void func_020b9ccc(void *p);
extern void func_ov002_0220af74(void *p);

void func_ov145_0229a8e8(void *obj);

int func_ov145_0229aa44(void)
{
    return 1;
}

int func_ov145_0229aa40(void)
{
    return 1;
}

int func_ov145_0229aa30(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov145_0229a9b8(UnkStruct_0229a9b8 *p)
{
    func_ov145_0229a778();
    func_ov145_0229a6c8(p);
    p->unk_C0 = 4;
    func_ov145_0229996c(p, 3);
    p->unk_C1 = 3;
    func_ov145_0229a678(p);
    func_ov002_02207f20(p, 10, 4, 0, 40);
    func_02002708(6);
    func_02002708(4);
    func_ov145_0229a8e8(p);
    func_ov145_02299658(p, 1);
    func_ov002_0220ab84(&p->unk_174, 0x65);
    func_ov002_02208090(p, 1);
}

void func_ov145_0229a990(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov145_0229a310(p);
    }
    func_ov145_0229a8e8(p);
}

void func_ov145_0229a958(void *p)
{
    func_ov092_02299324(func_020ee45c(p), 0x44, 1);
    func_ov002_02207f04(p, 0xa, 0, 0, 0x28);
    func_ov145_0229a8e8(p);
    func_ov002_02208090(p, 3);
}

void func_ov145_0229a928(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (arg), 5);
    } else {
        func_ov145_0229a8e8(arg);
    }
}

void func_ov145_0229a8e8(void *obj)
{
    int zero = 0;
    func_ov002_02207e80(obj, 6, zero, zero);
    func_ov002_02207e80(obj, 4, 0, 0x18 - *(int *) ((char *) obj + 0x9c));
    *(int *) ((char *) obj + 0x94) = func_ov002_02207f60(obj);
    func_ov145_0229a134(obj);
}

void func_ov145_0229a884(void *self)
{
    unsigned short *p1;
    unsigned char *p2;
    int i;
    int val;

    p1 = (unsigned short *) ((char *) self + 0xb4);
    *p1 = 0;
    p2 = (unsigned char *) ((char *) self + 0xc0);
    *p2 = 0;

    for (i = 0; i < 9; i++) {
        ((unsigned short *) ((char *) self + 0xcb4))[i] = 0xfff1;
    }

    ((unsigned char *) self)[0xc5] = 3;
    ((unsigned char *) self)[0xc6] = 0;

    func_ov145_0229a034(self);
    func_ov145_0229a010(self);
    func_ov145_02299fec(self);
    func_ov145_02299fc8(self);

    func_ov002_0220a580((char *) self + 0x12c);
}

void func_ov145_0229a844(void *self)
{
    func_ov145_02299da4(self);
    func_ov002_0220af74((char *) self + 0x174);
    func_020b9ccc((char *) self + 0xad8);
    func_020b9ccc((char *) self + 0xafc);
    func_020b9ccc((char *) self + 0xb20);
}
