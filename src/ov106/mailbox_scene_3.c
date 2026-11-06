/* mailbox_scene_3: 26 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229d29c @ 0x0229d29c, 0x48 bytes, Thumb
 * func_ov106_0229d24c @ 0x0229d24c, 0x50 bytes, Thumb
 * func_ov106_0229d20c @ 0x0229d20c, 0x40 bytes, Thumb
 * func_ov106_0229d1b8 @ 0x0229d1b8, 0x54 bytes, Thumb
 * func_ov106_0229d170 @ 0x0229d170, 0x48 bytes, Thumb
 * func_ov106_0229d128 @ 0x0229d128, 0x48 bytes, Thumb
 * func_ov106_0229d104 @ 0x0229d104, 0x24 bytes, Thumb
 * func_ov106_0229d0d0 @ 0x0229d0d0, 0x34 bytes, Thumb
 * func_ov106_0229d090 @ 0x0229d090, 0x40 bytes, Thumb
 * func_ov106_0229d074 @ 0x0229d074, 0x1c bytes, Thumb
 * func_ov106_0229d028 @ 0x0229d028, 0x4c bytes, Thumb
 * func_ov106_0229d00c @ 0x0229d00c, 0x1c bytes, Thumb
 * func_ov106_0229cfd0 @ 0x0229cfd0, 0x3c bytes, Thumb
 * func_ov106_0229cf8c @ 0x0229cf8c, 0x44 bytes, Thumb
 * func_ov106_0229cf0c @ 0x0229cf0c, 0x80 bytes, Thumb
 * func_ov106_0229cea8 @ 0x0229cea8, 0x64 bytes, Thumb
 * func_ov106_0229ce64 @ 0x0229ce64, 0x44 bytes, Thumb
 * func_ov106_0229ce38 @ 0x0229ce38, 0x2c bytes, Thumb
 * func_ov106_0229ce0c @ 0x0229ce0c, 0x2c bytes, Thumb
 * func_ov106_0229cde4 @ 0x0229cde4, 0x28 bytes, Thumb
 * func_ov106_0229cd88 @ 0x0229cd88, 0x5c bytes, Thumb
 * func_ov106_0229cd60 @ 0x0229cd60, 0x28 bytes, Thumb
 * func_ov106_0229cd20 @ 0x0229cd20, 0x40 bytes, Thumb
 * func_ov106_0229ccc8 @ 0x0229ccc8, 0x58 bytes, Thumb
 * func_ov106_0229cc84 @ 0x0229cc84, 0x44 bytes, Thumb
 * func_ov106_0229cc74 @ 0x0229cc74, 0x10 bytes, Thumb
 */

struct UnkStruct_0229cea8 {
    char pad_00[0xb6];
    unsigned char unk_B6;
    char pad_B7;
    unsigned char unk_B8;
    char pad_B9[0x20ff];
    char target[1];
};

typedef struct UnkStruct_0229ce64 {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    unsigned char unk_B4;
    char pad_B5[0xb58 - 0xb5];
    char unk_B58;
    char pad_B59[0x4180 - 0xb59];
    char unk_4180;
} UnkStruct_0229ce64;

typedef struct {
    char pad_00[0xb8];
    unsigned char b;
} UnkStruct_0229cc84;

extern int func_02066830(unsigned char *dst, int val);
extern int func_ov106_0229d3a0(int a, int b);
extern int func_ov106_0229d360(int a, int b);
extern void func_ov094_0229b8b4(int addr, int val, int c);
extern int func_ov106_0229d390(char *a, char *b);
extern int func_ov094_0229b8d8(char *addr, int value);
extern int func_02065ec0(int);
extern int func_020984e8(void);
extern int func_02066648(int);
extern int func_0204bd20(int, int);
extern int func_020996ac(int);
extern int func_0203cd2c(int, void *, int, int);
extern int func_ov094_0229b384(void *p, int n);
extern int func_ov094_0229b328(int a, int b);
extern void func_ov094_0229a898(void *, int, int);
extern void func_ov094_0229b794(void *, int);
extern int func_ov094_0229b788(int, int);
extern int func_ov094_0229b30c(void *p, int v);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229b950(char *addr, int val);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_0229b938(char *p, int v);
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;
extern int func_0206fe54(void);
extern void func_0208aa60(unsigned char *, int, int);
extern int func_ov094_0229b9b4(unsigned char *, unsigned char *, int);
extern void func_ov002_02207cf0(void *p);
extern void func_ov002_02207cf8(void *p);
extern int func_ov106_0229c364(UnkStruct_0229ce64 *obj, int arg);
extern void func_ov094_0229b5e8(void *p, int v1, int v2, void *p2);
extern int func_ov002_02209f3c(void *ptr);
extern int func_ov002_02209f14(void *ptr);
extern int func_ov002_02209d84(unsigned char *p);
extern int func_ov002_02209d7c(unsigned char *p);
extern void func_ov094_0229b890(char *, int);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int v);
extern int func_ov106_0229d384(unsigned char *p, unsigned char c);
extern void func_ov106_0229ca3c(unsigned char *p);

void func_ov106_0229d24c(int a, int b, int c);
int func_ov106_0229d20c(char *a, char *b);
void func_ov106_0229d1b8(int a, int b);
int func_ov106_0229d090(void *a, void *b);
void func_ov106_0229cd60(void *self, int arg);
int func_ov106_0229cc84(UnkStruct_0229cc84 *arg0);
int func_ov106_0229cc74(void *param);

int func_ov106_0229d29c(unsigned char *a, int b)
{
    if (func_ov106_0229d090((void *) a, (void *) b) == 0) {
        func_02066830(a + 0x4280, func_ov106_0229d20c((char *) a, (char *) b));
        func_ov106_0229d24c((int) a, (unsigned char) (*(unsigned char *) (a + 0xb7)), (int) (a + 0x4280));
    }
    func_ov106_0229cd60((void *) a, b);
    return 1;
}

void func_ov106_0229d24c(int a, int b, int c)
{
    if (func_ov106_0229d3a0(a, b) || func_ov106_0229d390((char *) a, (char *) b)) {
        int t = func_ov106_0229d360(a, b);
        func_ov094_0229b8b4(a + 0xb58, t, c);
        if (func_ov106_0229d3a0(a, b)) {
            func_ov106_0229d1b8(a, c);
        }
    }
}

int func_ov106_0229d20c(char *a, char *b)
{
    if (func_ov106_0229d3a0((int) a, (int) b) != 0 || func_ov106_0229d390(a, b) != 0) {
        return func_ov094_0229b8d8(a + 0xb58, func_ov106_0229d360((int) a, (int) b));
    } else {
        return 0;
    }
}

void func_ov106_0229d1b8(int a, int b)
{
    if (func_02065ec0(b) == 2 || func_02065ec0(b) == 3) {
        int x = func_020984e8();
        unsigned short s = 0xfff1;
        s = (unsigned short) func_0204bd20(func_02066648(b), 4);
        func_0203cd2c(func_020996ac(x), &s, 0, 1);
    }
}

int func_ov106_0229d170(void *p, int n)
{
    if (!(func_ov106_0229d3a0((int) p, n) == 0 && func_ov106_0229d390((char *) p, (char *) n) == 0)) {
        return func_ov094_0229b384((char *) p + 0xb58, func_ov106_0229d360((int) p, n));
    }

    if (n == 0x1f) {
        return 0xbc;
    }
    return 0;
}

int func_ov106_0229d128(int a, int b)
{
    if (func_ov106_0229d3a0(a, b) != 0 || func_ov106_0229d390((char *) a, (char *) b) != 0) {
        return func_ov094_0229b328(a + 0xb58, func_ov106_0229d360(a, b)) - 0x10;
    } else {
        if (b == 31) {
            return 0xb6;
        } else {
            return 0;
        }
    }
}

void func_ov106_0229d104(void *arg0)
{
    func_ov094_0229a898((char *) arg0 + 0xf8, 0, 0xe);
    func_ov094_0229b794((char *) arg0 + 0xb58, 4);
}

int func_ov106_0229d0d0(int a0, int a1)
{
    if (func_ov106_0229d3a0(a0, a1)) {
        return func_ov094_0229b788(a0 + 0xb58, func_ov106_0229d360(a0, a1));
    }
    return 0;
}

int func_ov106_0229d090(void *a, void *b)
{
    if (func_ov106_0229d3a0((int) a, (int) b) != 0 || func_ov106_0229d390((char *) a, (char *) b) != 0) {
        return func_ov094_0229b30c((char *) a + 0xb58, func_ov106_0229d360((int) a, (int) b));
    } else {
        return 1;
    }
}

void func_ov106_0229d074(void *self)
{
    func_ov094_0229ab5c((char *) self + 0xf8);
    func_ov094_0229b98c((char *) self + 0xb58);
}

void func_ov106_0229d028(char *p1, int p2)
{
    if (func_ov106_0229d3a0((int) p1, p2) != 0 || func_ov106_0229d390(p1, (char *) p2) != 0) {
        int tmp;
        tmp = func_ov106_0229d360((int) p1, p2);
        func_ov094_0229b950(p1 + 0xb58, tmp);
        func_ov094_0229ab5c((void *) (p1 + 0xf8));
    } else {
        func_ov106_0229d074((void *) p1);
    }
}

void func_ov106_0229d00c(void *self)
{
    func_ov094_0229ab0c((char *) self + 0xf8);
    func_ov094_0229b944((char *) self + 0xb58);
}

void func_ov106_0229cfd0(char *p, char *q)
{
    if (func_ov106_0229d3a0((int) p, (int) q) != 0 || func_ov106_0229d390(p, q) != 0) {
        func_ov094_0229b938(p + 0xb58, func_ov106_0229d360((int) p, (int) q));
    }
}

int func_ov106_0229cf8c(void *receiver)
{
    int diff1;
    int diff2;

    diff1 = data_021f6c60 - data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 8) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 8) {
        return 1;
    }

    return 0;
}

void func_ov106_0229cf0c(unsigned char *self)
{
    int v6;
    int v4;
    int v2;

    v6 = func_ov106_0229d170((void *) self, (unsigned char) self[0xb6]) - 0x6d;
    v4 = func_ov106_0229d128((int) self, (unsigned char) self[0xb6]) - 0x78;
    if (func_0206fe54()) {
        v4 -= 8;
    }
    func_0208aa60(self + 0x21b8, v6, v4);

    if (func_ov106_0229d3a0((int) self, (unsigned char) self[0xb6]) == 0) {
        if (func_ov106_0229d390((char *) self, (char *) self[0xb6]) == 0) {
            return;
        }
    }

    v2 = func_ov106_0229d360((int) self, (unsigned char) self[0xb6]);
    func_ov094_0229b9b4(self + 0x0b58, self + 0x21b8, v2);
}

void func_ov106_0229cea8(struct UnkStruct_0229cea8 *self)
{
    if (func_ov106_0229d3a0((int) self, (unsigned char) self->unk_B8) != 0 ||
        func_ov106_0229d390((char *) self, (char *) self->unk_B8) != 0) {
        if (func_ov106_0229d090((void *) self, (void *) self->unk_B8) != 0) {
            func_ov002_02207cf0(self->target);
        } else {
            self->unk_B6 = self->unk_B8;
            func_ov002_02207cf8(self->target);
        }
    } else {
        func_ov002_02207cf0(self->target);
    }
}

void func_ov106_0229ce64(UnkStruct_0229ce64 *obj)
{
    if (func_ov106_0229c364(obj, 0x40) != 0) {
        return;
    }
    if (obj->unk_B4 == 0) {
        return;
    }
    if (obj->unk_B4 != 1) {
        return;
    }
    func_ov094_0229b5e8(&obj->unk_B58, obj->unk_AC, obj->unk_B0, &obj->unk_4180);
}

void func_ov106_0229ce38(unsigned char *self)
{
    unsigned int tmp;
    unsigned int tmp2;

    tmp = *(unsigned int *) (self + 0xa4);
    tmp += data_021f6c58;
    *(unsigned int *) (self + 0xac) = tmp;

    tmp2 = *(unsigned int *) (self + 0xa8);
    tmp2 += data_021f6c54;
    *(unsigned int *) (self + 0xb0) = tmp2;
}

void func_ov106_0229ce0c(char *p)
{
    *(int *) (p + 0xac) = func_ov002_02209f3c(p + 0x22a0) - 2;
    *(int *) (p + 0xb0) = func_ov002_02209f14(p + 0x22a0) - 4;
}

void func_ov106_0229cde4(unsigned char *p)
{
    *(int *) (p + 0xac) = func_ov002_02209d84(p + 0x2288);
    *(int *) (p + 0xb0) = func_ov002_02209d7c(p + 0x2288);
}

void func_ov106_0229cd88(char *self, char *arg)
{
    int result, temp;

    if (func_ov106_0229d3a0((int) self, (int) arg) == 0) {
        if (func_ov106_0229d390(self, arg) == 0) {
            return;
        }
    }
    result = func_ov106_0229d360((int) self, (int) arg);
    *(self + 0xb4) = 1;
    temp = func_ov094_0229b8d8(self + 0xb58, result);
    func_02066830((unsigned char *) (self + 0x4180), temp);
    func_ov094_0229b890(self + 0xb58, result);
}

void func_ov106_0229cd60(void *self, int arg)
{
    if (((unsigned char *) self)[0xb4] == 1) {
        func_ov106_0229d24c((int) self, arg, (int) ((char *) self + 0x4180));
    }
    ((unsigned char *) self)[0xb4] = 0;
}

void func_ov106_0229cd20(unsigned char *self, void *arg)
{
    if (self[0xb4] == 1) {
        func_02066830((unsigned char *) (self + 0x4280), (int) (self + 0x4180));
        func_ov106_0229cd88((char *) self, (char *) arg);
        func_ov106_0229d24c((int) self, (int) arg, (int) (self + 0x4280));
    }
}

void func_ov106_0229ccc8(unsigned char *p)
{
    func_ov002_0220a0b4(p + 0x22a0, func_ov106_0229cc84((UnkStruct_0229cc84 *) p), func_ov106_0229cc74((void *) p));
    if (func_ov106_0229d384(p, p[0xb8]) != 0) {
        func_ov002_0220a374(p + 0x22a0, 7);
    } else {
        func_ov002_0220a374(p + 0x22a0, 1);
    }
    func_ov106_0229ca3c(p);
}

int func_ov106_0229cc84(UnkStruct_0229cc84 *arg0)
{
    int ret;
    ret = func_ov106_0229d170(arg0, arg0->b);
    if (func_ov106_0229c364((UnkStruct_0229ce64 *) arg0, 0x20) != 0) {
        ret += 0x100;
    } else if (func_ov106_0229c364((UnkStruct_0229ce64 *) arg0, 0x10) != 0) {
        ret -= 0x100;
    }
    return ret + 8;
}

int func_ov106_0229cc74(void *param)
{
    return func_ov106_0229d128((int) param, (unsigned char) (*(unsigned char *) ((char *) param + 0xb8)));
}
