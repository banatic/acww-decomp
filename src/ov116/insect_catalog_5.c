/* insect_catalog_5: 12 functions, module ov116
 * mwccarm 1.2/base -O4,s
 * func_ov116_0229e5b8 @ 0x0229e5b8, 0x4 bytes, Thumb
 * func_ov116_0229e5b4 @ 0x0229e5b4, 0x4 bytes, Thumb
 * func_ov116_0229e5a4 @ 0x0229e5a4, 0x10 bytes, Thumb
 * func_ov116_0229e50c @ 0x0229e50c, 0x98 bytes, Thumb
 * func_ov116_0229e4cc @ 0x0229e4cc, 0x3e bytes, Thumb
 * func_ov116_0229e47c @ 0x0229e47c, 0x50 bytes, Thumb
 * func_ov116_0229e454 @ 0x0229e454, 0x28 bytes, Thumb
 * func_ov116_0229e41c @ 0x0229e41c, 0x38 bytes, Thumb
 * func_ov116_0229e3e4 @ 0x0229e3e4, 0x36 bytes, Thumb
 * func_ov116_0229e3a8 @ 0x0229e3a8, 0x3c bytes, Thumb
 * func_ov116_0229e384 @ 0x0229e384, 0x24 bytes, Thumb
 * func_ov116_0229e36c @ 0x0229e36c, 0x16 bytes, Thumb
 */

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} Object;

extern void func_020ee470(void *parameter0);
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern unsigned short data_021fbe40[];
extern int func_020ee45c(void *obj);
extern void func_ov090_022993cc(int r, unsigned char c);
extern unsigned char *func_ov002_022080a0(void *obj, unsigned char value);
extern void func_ov116_0229e2e0(void);
extern void func_ov116_0229e2c8(void *);
extern void func_ov116_0229e2b0(void *);
extern void func_02002708(int);
extern void func_ov116_0229dda8(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(void *, int);
extern void func_ov116_0229df6c(void *);
extern void func_ov116_0229deb4(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov114_0229c8b4(void *);
extern int func_ov002_02207f3c(void *arg0, int arg1);
extern void func_020027f0(int arg0);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov114_0229d8d0(void *param1, int param2, int param3, int param4, int param5);
extern void func_ov114_0229d8ac(void *p);
extern void func_ov116_0229df50(void *p);

int func_ov116_0229e4cc(Object *obj, int x);
void func_ov116_0229e3a8(void *p);

int func_ov116_0229e5b8(void)
{
    return 1;
}

int func_ov116_0229e5b4(void)
{
    return 1;
}

int func_ov116_0229e5a4(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

int func_ov116_0229e50c(void *p)
{
    func_0206f58c();
    if (func_0206f56c() != 0) {
        return func_ov116_0229e4cc((Object *) p, 7);
    }
    {
        unsigned char b = *(unsigned char *) ((char *) p + 0x8d);
        if (b != 0 && b != 2) {
            return 0;
        }
    }
    {
        int r4 = -1;
        int c = func_0206fe60();
        if (c != 0) {
            r4 = func_ov090_022990e0();
        } else {
            unsigned short flags = data_021fbe40[1];
            if (flags & 2) {
                r4 = 7;
            } else if (flags & 0x800) {
                r4 = 0;
            } else if (flags & 0x400) {
                r4 = 5;
            } else if (flags & 4) {
                r4 = 4;
            }
        }
        return func_ov116_0229e4cc((Object *) p, r4);
    }
}

int func_ov116_0229e4cc(Object *obj, int x)
{
    int r;
    r = func_020ee45c(obj);
    if (x != -1 && x != 3) {
        func_ov090_022993cc(r, (unsigned char) x);
        obj->unk_8C = 2;
        func_ov002_022080a0(obj, 1);
        return 1;
    }
    return 0;
}

void func_ov116_0229e47c(void *r0)
{
    void *r4 = r0;
    func_ov116_0229e2e0();
    func_ov116_0229e2c8(r4);
    func_ov116_0229e2b0(r4);
    func_ov002_02207f20(r4, 0xb, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(6);
    func_ov116_0229dda8(r4, 1);
    func_ov116_0229e3a8(r4);
    func_ov002_02208090(r4, 1);
}

void func_ov116_0229e454(void *arg0)
{
    if (func_ov002_02207f48(arg0, 0) != 0) {
        func_ov002_022080a0(arg0, 2);
        func_ov116_0229df6c(arg0);
    }
    func_ov116_0229e3a8(arg0);
}

void func_ov116_0229e41c(void *p)
{
    func_ov116_0229deb4(p);
    func_ov002_02207f04(p, 0xb, 0, 0, 0x30);
    func_ov116_0229e3a8(p);
    func_ov002_02208090(p, 3);
    p = (void *) ((char *) p + 0xf8);
    func_ov114_0229c8b4(p);
}

void func_ov116_0229e3e4(void *arg0)
{
    if (func_ov002_02207f3c(arg0, 0)) {
        func_020027f0(3);
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0(arg0, 5);
    } else {
        func_ov116_0229e3a8(arg0);
    }
}

void func_ov116_0229e3a8(void *p)
{
    func_ov002_02207e80(p, 3, 0, 0);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
    ((int *) p)[0x1424 / 4] = func_ov002_02207f60(p);
}

void func_ov116_0229e384(void *param1)
{
    *(unsigned short *) ((char *) param1 + 0x1428) = 0;
    func_ov114_0229d8d0((char *) param1 + 0xf8, 3, 6, 4, 1);
}

void func_ov116_0229e36c(void *p)
{
    func_ov114_0229d8ac((char *) p + 0xf8);
    func_ov116_0229df50(p);
}
