/* mailbox_scene_5: 13 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229da80 @ 0x0229da80, 0x54 bytes, Thumb
 * func_ov106_0229d9fc @ 0x0229d9fc, 0x84 bytes, Thumb
 * func_ov106_0229d978 @ 0x0229d978, 0x84 bytes, Thumb
 * func_ov106_0229d948 @ 0x0229d948, 0x2e bytes, Thumb
 * func_ov106_0229d8e0 @ 0x0229d8e0, 0x68 bytes, Thumb
 * func_ov106_0229d860 @ 0x0229d860, 0x80 bytes, Thumb
 * func_ov106_0229d810 @ 0x0229d810, 0x4e bytes, Thumb
 * func_ov106_0229d7d4 @ 0x0229d7d4, 0x3c bytes, Thumb
 * func_ov106_0229d7ac @ 0x0229d7ac, 0x28 bytes, Thumb
 * func_ov106_0229d790 @ 0x0229d790, 0x1c bytes, Thumb
 * func_ov106_0229d75c @ 0x0229d75c, 0x34 bytes, Thumb
 * func_ov106_0229d73c @ 0x0229d73c, 0x20 bytes, Thumb
 * func_ov106_0229d724 @ 0x0229d724, 0x16 bytes, Thumb
 */

struct UnkStruct_0229da80 {
    unsigned char flag;
};

struct Big {
    char pad_00[0xbe];
    struct UnkStruct_0229da80 sub;
    char pad_BF[0x22a0 - (0xbe + 1)];
    char unk_22A0;
    char pad_22A1[0x3fb4 - (0x22a0 + 1)];
    char unk_3FB4;
};

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void *func_ov002_0220a720(void *, int);
extern void func_0200467c(int);
extern int func_ov002_0220a700(char *p);
extern int func_0208e4bc(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int x);
extern int func_ov002_0220a72c(char *p, int x);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov002_02207e9c(char *p, int a, int b);
extern int func_ov002_0220b7ec(char *p);
extern int func_ov002_0220b7b8(char *);
extern int func_ov002_02207f3c(char *, int);
extern int func_ov002_02207f60(char *);
extern void func_ov002_0220a690(char *);
extern void func_ov002_02207eb4(char *, int, int);
extern int func_ov002_0220ab84(char *, int);
extern void *func_ov002_0220ad0c(char *);
extern void func_ov002_02208090(char *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207f48(void *p, int val);
extern int func_ov002_0220b57c(void *p);
extern int func_ov002_0220b5ec(void *p, int a);
extern int func_ov002_0220b59c(void *p, int a);
extern void func_ov106_0229cc50(void *p);
extern void func_ov106_0229c344(unsigned char *, int);
extern int func_ov106_0229d454(void *);
extern int func_ov106_0229d48c(void *);
extern void func_ov106_0229d414(void *, int);
extern void func_ov106_0229d4ac(void *, int, int);
extern void func_ov106_0229cd60(int, unsigned char);
extern void func_ov106_0229cde4(int);
extern int func_ov002_02209d8c(int);
extern void func_ov094_022999d8(void);
extern int func_ov094_0229b19c(void *);
extern void func_ov106_0229d074(void *);
extern void func_ov106_0229ccc8(void *);
extern void func_ov106_0229cea8(void *);
extern void func_ov106_0229d028(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);

void func_ov106_0229d73c(void *param);

void func_ov106_0229da80(struct Big *p)
{
    struct UnkStruct_0229da80 *s;
    if (func_0208e484(&p->unk_22A0) == 0) {
        return;
    }
    func_ov002_02208098((void *) (p), 0x1f);
    s = &p->sub;
    if (s->flag != 0) {
        func_ov002_0220a720(&p->unk_3FB4, 4);
        func_0200467c(0x28);
    } else {
        func_ov002_0220a720(&p->unk_3FB4, 3);
        func_0200467c(0x27);
    }
}

void func_ov106_0229d9fc(char *param)
{
    if (func_ov002_0220a700(param + 0x3fb4) != 0) {
        int v4;
        int v6;
        int v2;

        if (func_0208e4bc(param + 0x22a0) == 0) {
            return;
        }
        v4 = func_ov002_0220a6e0(param + 0x3fb4);
        v6 = func_ov002_0220a768(param + 0x3fb4, -1);
        v2 = func_ov002_0220a72c(param + 0x3fb4, -1);
        func_ov002_0220a0b4(param + 0x22a0, v4 + v6, v4 + v2);
    } else {
        func_ov106_0229cc50((void *) param);
        func_ov002_02208098((void *) (param), 0x20);
        func_ov002_02207e9c(param, 0, 0);
        func_ov002_0220b7ec(param + 0x26f8);
    }
}

void func_ov106_0229d978(char *obj)
{
    int v = func_ov002_0220b7b8(obj + 0x26f8) & func_ov002_02207f3c(obj, -1);
    *(int *) (obj + 0xa0) = func_ov002_02207f60(obj);
    if (v) {
        func_ov002_0220a690(obj + 0x3fb4);
        if (*(unsigned char *) (obj + 0xbe) == 0) {
            func_ov002_02207eb4(obj, 0, 0);
            func_ov002_0220ab84(obj + 0x3fb4, 0x88);
            func_ov002_02208098((void *) (obj), 0x21);
        } else {
            func_ov002_0220ad0c(obj + 0x3fb4);
            func_ov002_02208090(obj, 4);
            func_ov002_022080a0((void *) (obj), 1);
        }
    }
}

void func_ov106_0229d948(void *obj)
{
    int a;
    int b;
    char *p;

    a = func_ov002_02207f48(obj, -1);
    b = func_ov002_02207f60((char *) obj);
    p = (char *) obj;
    p += 0xA0;
    *(int *) p = b;
    if (a != 0) {
        func_ov106_0229d73c(obj);
    }
}

void func_ov106_0229d8e0(char *self)
{
    if (func_ov002_0220b57c(self + 0x2b3c) != 0) {
        if (func_0208e4bc((char *) (self + 0x22a0)) != 0) {
            int a = func_ov002_0220b5ec(self + 0x2b3c, 1);
            int b = func_ov002_0220b59c(self + 0x2b3c, 1);
            func_ov002_0220a0b4((char *) (self + 0x22a0), a, b);
        }
    } else {
        func_ov106_0229cc50(self);
        func_ov002_02208090((char *) self, 9);
        func_ov002_022080a0((void *) (self), 1);
    }
}

void func_ov106_0229d860(unsigned char *p)
{
    if (func_ov002_0220a700((char *) (p + 0x3fb4)) != 0) {
        if (func_0208e4bc((char *) (p + 0x22a0)) != 0) {
            int a = func_ov002_0220a6e0((char *) (p + 0x3fb4));
            int b = func_ov002_0220a768((char *) (p + 0x3fb4), -1);
            int c = func_ov002_0220a72c((char *) (p + 0x3fb4), -1);
            func_ov002_0220a0b4((char *) (p + 0x22a0), a + b, a + c);
        }
    } else {
        func_ov106_0229cc50((void *) p);
        p[0x8c] = 4;
        func_ov106_0229c344(p, 0x100);
        func_ov002_022080a0((void *) (p), 1);
    }
}

void func_ov106_0229d810(void *self)
{
    int v;
    int w;

    v = func_ov106_0229d454(self);
    if (v == 0x20) {
        *((unsigned char *) self + 0xb8) = 0x1f;
        func_ov106_0229d73c(self);
    } else {
        w = func_ov106_0229d48c(self);
        if (w == 0x20) {
            func_ov106_0229d414(self, 6);
        } else {
            func_ov106_0229d4ac(self, v, w);
            func_ov002_02208098((void *) (self), 0x25);
        }
    }
}

void func_ov106_0229d7d4(int param)
{
    if (func_ov002_02209d8c(param + 0x2288) != 0) {
        func_ov106_0229cd60(param, *(unsigned char *) (param + 0xb7));
        func_ov002_02208098((void *) (param), 0x24);
        func_ov094_022999d8();
    } else {
        func_ov106_0229cde4(param);
    }
}

void func_ov106_0229d7ac(void *self)
{
    if (func_ov094_0229b19c((char *) self + 0xb58)) {
        ((char *) self)[0xb4] = 0;
        func_ov106_0229d73c(self);
    }
}

void func_ov106_0229d790(void *p)
{
    func_ov106_0229cc50(p);
    func_ov106_0229d074(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov106_0229d75c(void *r0)
{
    unsigned char *p;
    unsigned char *q;

    p = (unsigned char *) r0;
    q = p + 0xb6;
    *q = 0x20;
    func_ov106_0229ccc8(r0);
    func_ov002_02207fc0(r0);
    func_ov106_0229cea8(r0);
    func_ov002_02208098((void *) (r0), 7);
    q = p + 0xb8;
    func_ov106_0229d028(r0, *q);
}

void func_ov106_0229d73c(void *param)
{
    if (func_0206fe60()) {
        func_ov106_0229d790(param);
    } else {
        func_ov106_0229d75c(param);
    }
}

void func_ov106_0229d724(void *ptr)
{
    func_ov106_0229cc50(ptr);
    func_ov002_02208098((void *) (ptr), 0x1c);
}
