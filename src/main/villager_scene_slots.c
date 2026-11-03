/* villager_scene_slots: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202e364 @ 0x0202e364, 0x48 bytes, Thumb
 * func_0202e318 @ 0x0202e318, 0x4c bytes, Thumb
 * func_0202e1fc @ 0x0202e1fc, 0x11c bytes, Thumb
 * func_0202e1dc @ 0x0202e1dc, 0x20 bytes, Thumb
 * func_0202e1a0 @ 0x0202e1a0, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    unsigned char unk_10;
    char pad_11[3];
    int unk_14;
} UnkStruct_0202e1fc;

extern int func_0201bdb4(void *);
extern void func_0202e58c(void *);
extern int func_020644cc(int);
extern void func_0201cd5c(void *);
extern void func_0201cde8(void *);
extern int func_02082f78(int);
extern int func_02078a5c(int);
extern int func_02055478(int, int);
extern int func_02054354(int, int);
extern int func_0201bd48(void *self);
extern int func_0208308c(void *p);
extern int func_0201a304(void *a, void *self);
extern int func_0201691c(UnkStruct_0202e1fc *param0, void *param1, int param2);
extern int data_020c8120;
extern void func_02019e04(void *self, void *other, int a3, int a4, unsigned int a5, unsigned int a6, short a7, unsigned int a8,
                          unsigned int a9);
extern int func_02080ce4(int r0);
extern int func_0202e058(void *a, void *self, unsigned short *c);
extern unsigned short func_0201c444(void *ptr);
extern void func_02089c20(void *p, int a, int b, int c, int d, int e, int f, unsigned char g, int h);
extern int func_02082578(void *a, void *b);
extern int func_0203efdc(char *);
extern int func_02082568(void *);
extern int func_0201b744(unsigned char *);
extern void func_02083068(void *);
extern void func_0202df00(void *);
extern int func_0201cd3c(void *);

int func_0202e364(void *r0)
{
    void *r4 = r0;
    if (func_0201bdb4(r4) == 0) {
        return 0;
    }
    func_0202e58c(r4);
    *(int *) ((char *) r4 + 0x644) = 0;
    *(char *) ((char *) r4 + 0x824) = (char) func_020644cc(2);
    func_0201cd5c((char *) r4 + 0x83c);
    func_0201cde8(r4);
    return 1;
}

int func_0202e318(int a)
{
    int X;
    int Y;
    int Z;
    X = func_02082f78(a + 0x828);
    Y = func_02078a5c(X);
    if (func_02055478(a + 0xec, Y) == 0) {
        return 0;
    }
    Z = func_02078a5c(X);
    if (func_02054354(a + 0xec, Z) == 0) {
        return 0;
    }
    return 1;
}

int func_0202e1fc(void *self)
{
    unsigned short buf;
    unsigned char *ptr;

    buf = 0x11a8;

    if (func_0201bd48(self) == 0) {
        return 0;
    }
    if (func_02082f78((int) ((char *) self + 0x828)) == 0) {
        if (func_0208308c((char *) self + 0x828) == 0) {
            return 0;
        }
        if (func_0202e318((int) self) == 0) {
            return 0;
        }
    }
    if (func_0201a304((char *) self + 0x2ac, self) == 0) {
        return 0;
    }
    if (func_0201691c((UnkStruct_0202e1fc *) ((char *) self + 0x334), self, data_020c8120) == 0) {
        return 0;
    }

    func_02019e04((char *) self + 0x564, self, 0, 1, 0, 0, 0, 0, 0);

    ptr = *(unsigned char **) ((char *) self + 0x830);
    if (ptr != 0) {
        buf = *(unsigned short *) func_02080ce4((int) ptr);
    }

    if (func_0202e058((char *) self + 0x64c, self, &buf) == 0) {
        return 0;
    }

    func_02089c20((char *) self + 0x4cc, (int) self, 0x1000, 0x2000, 8, 0x2fc, 2, (unsigned char) func_0201c444(self), 0x1000);

    if (func_02082578(self, (char *) self + 0xea) != 0) {
        goto ok;
    }
    return 0;
ok:
    return 1;
}

int func_0202e1dc(void *arg0)
{
    void *r4;
    int r0;

    r4 = arg0;
    r0 = func_0203efdc(arg0);
    if (r0 == 0) {
        return 0;
    }
    r4 = (char *) r4 + 0xea;
    func_02082568(r4);
    return 1;
}

int func_0202e1a0(void *r4)
{
    if (func_0201b744(r4) == 0) {
        return 0;
    }
    func_02083068((void *) ((char *) r4 + 0x828));
    func_0202df00((void *) ((char *) r4 + 0x64c));
    func_0201cd3c((void *) ((char *) r4 + 0x83c));
    return 1;
}
