/* music_list_scene_3: 10 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229afc8 @ 0x0229afc8, 0x4 bytes, Thumb
 * func_ov144_0229afc4 @ 0x0229afc4, 0x4 bytes, Thumb
 * func_ov144_0229afb4 @ 0x0229afb4, 0x10 bytes, Thumb
 * func_ov144_0229af50 @ 0x0229af50, 0x64 bytes, Thumb
 * func_ov144_0229af28 @ 0x0229af28, 0x28 bytes, Thumb
 * func_ov144_0229aed4 @ 0x0229aed4, 0x54 bytes, Thumb
 * func_ov144_0229aea4 @ 0x0229aea4, 0x30 bytes, Thumb
 * func_ov144_0229ae64 @ 0x0229ae64, 0x3e bytes, Thumb
 * func_ov144_0229ae24 @ 0x0229ae24, 0x40 bytes, Thumb
 * func_ov144_0229adf0 @ 0x0229adf0, 0x34 bytes, Thumb
 */

extern void func_020ee470(void *parameter0);
extern void func_ov144_0229ad24(void);
extern void func_ov144_0229ac90(void *);
extern void func_ov144_02299ea8(void *);
extern void func_ov144_0229ac40(void *);
extern void func_02002708(int);
extern void func_ov144_02299670(void *, int);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern int func_ov002_02207f48(void *param, int flag);
extern unsigned char *func_ov002_022080a0(void *param, unsigned char value);
extern int func_ov144_0229a7c8(void *param);
extern int func_020ee45c(void *);
extern int func_ov144_02299680(void *, int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov144_0229a3dc(void *p);
extern void func_ov144_0229a328(void *);
extern void func_ov144_0229a29c(void *);
extern void func_ov002_0220a580(void *);
extern void func_ov144_0229a040(void *p);
extern void func_ov002_0220af74(void *p);
extern void func_020b9ccc(void *p);

void func_ov144_0229ae64(void *p);

int func_ov144_0229afc8(void)
{
    return 1;
}

int func_ov144_0229afc4(void)
{
    return 1;
}

int func_ov144_0229afb4(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov144_0229af50(void *r0)
{
    void *r4 = r0;
    func_ov144_0229ad24();
    func_ov144_0229ac90(r4);
    func_ov144_02299ea8(r4);
    func_ov144_0229ac40(r4);
    func_ov002_02207f20(r4, 10, 4, 0, 24);
    func_02002708(6);
    func_02002708(4);
    func_ov144_0229ae64(r4);
    func_ov144_02299670(r4, 1);
    func_ov002_0220ab84((char *) r4 + 0x170, 0x65);
    func_ov002_02208090(r4, 1);
}

void func_ov144_0229af28(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0(param, 2);
        func_ov144_0229a7c8(param);
    }
    func_ov144_0229ae64(param);
    return;
}

void func_ov144_0229aed4(void *self)
{
    int tmp;
    tmp = func_020ee45c(self);
    if (func_ov144_02299680(self, 0x20)) {
        func_ov092_02299324(tmp, 0x23, 1);
    } else {
        func_ov092_02299324(tmp, 0x44, 1);
    }
    func_ov002_02207f04(self, 0xa, 0, 0, 0x18);
    func_ov144_0229ae64(self);
    func_ov002_02208090(self, 3);
}

void func_ov144_0229aea4(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0(param, 5);
    } else {
        func_ov144_0229ae64(param);
    }
}

void func_ov144_0229ae64(void *p)
{
    int x;
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0x18 - *(int *) ((char *) p + 0x9c));
    x = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x94) = x;
    func_ov144_0229a3dc(p);
}

void func_ov144_0229ae24(void *self)
{
    unsigned short *p;
    int i;
    unsigned short *q;

    p = (unsigned short *) ((char *) self + 0xb4);
    *p = 0;
    for (i = 0; i < 9; i++) {
        q = (unsigned short *) ((char *) self + 0x8f8 + i * 2);
        *q = 0xfff1;
    }
    func_ov144_0229a328(self);
    func_ov144_0229a29c(self);
    func_ov002_0220a580((char *) self + 0x128);
}

void func_ov144_0229adf0(void *obj)
{
    func_ov144_0229a040(obj);
    func_ov002_0220af74((void *) ((char *) obj + 0x170));
    func_020b9ccc((void *) ((char *) obj + 0x708));
    func_020b9ccc((void *) ((char *) obj + 0x72c));
}
