/* bank_menu_3: 16 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229b23c @ 0x0229b23c, 0x40 bytes, Thumb
 * func_ov132_0229b214 @ 0x0229b214, 0x28 bytes, Thumb
 * func_ov132_0229b1b0 @ 0x0229b1b0, 0x62 bytes, Thumb
 * func_ov132_0229b184 @ 0x0229b184, 0x2c bytes, Thumb
 * func_ov132_0229b158 @ 0x0229b158, 0x2c bytes, Thumb
 * func_ov132_0229b140 @ 0x0229b140, 0x16 bytes, Thumb
 * func_ov132_0229b124 @ 0x0229b124, 0x1c bytes, Thumb
 * func_ov132_0229b104 @ 0x0229b104, 0x20 bytes, Thumb
 * func_ov132_0229b0d0 @ 0x0229b0d0, 0x34 bytes, Thumb
 * func_ov132_0229b068 @ 0x0229b068, 0x68 bytes, Thumb
 * func_ov132_0229aff8 @ 0x0229aff8, 0x70 bytes, Thumb
 * func_ov132_0229af88 @ 0x0229af88, 0x70 bytes, Thumb
 * func_ov132_0229af54 @ 0x0229af54, 0x34 bytes, Thumb
 * func_ov132_0229af04 @ 0x0229af04, 0x50 bytes, Thumb
 * func_ov132_0229aed8 @ 0x0229aed8, 0x2c bytes, Thumb
 * func_ov132_0229aeac @ 0x0229aeac, 0x2c bytes, Thumb
 */

typedef struct {
    char pad_00[0x94];
    char sub;
    char pad_95[0x146D];
    unsigned char flag;
} UnkStruct_0229af04;

struct UnkStruct_0229aeac {
    char pad_00[0x1502];
    unsigned char flag;
};

extern int func_0208e484(unsigned char *p);
extern void func_ov132_0229adfc(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char byte);
extern int func_ov002_0220a700(unsigned char *);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220a6e0(unsigned char *);
extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a72c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern unsigned char *func_ov002_022080a0(unsigned char *, unsigned char value);
extern void func_ov132_0229ae90(void *);
extern int func_ov002_0220b8ac(char *p, int n);
extern void func_0208e5cc(char *p);
extern void func_ov002_02207fc0(void *a);
extern int func_0206fe60(void);
extern void func_0206fc4c(int);
extern void *func_ov002_0220a720(unsigned char *, int);
extern void func_ov002_02208090(unsigned char *, int);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_0200467c(int cmd);
extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_020983f0(int *);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern int func_02099734(int);
extern int func_02098cc0(int, int, int);
extern int func_ov002_0220b9b8(void *a, void *b, int c, int d);
extern void func_0208e5c4(void *a);
extern void func_ov002_0220a374(void *addr, int val);
extern void *data_ov132_0229b904[];
extern int data_ov132_0229b910[];

void func_ov132_0229b104(int r0);
void func_ov132_0229b0d0(unsigned char *p);
void func_ov132_0229aff8(char *arg);
void func_ov132_0229af88(void *param);
void func_ov132_0229af54(void *r0, unsigned char r1);
void func_ov132_0229af04(UnkStruct_0229af04 *p);
void *func_ov132_0229aed8(void *self);
int func_ov132_0229aeac(struct UnkStruct_0229aeac *obj);

void func_ov132_0229b23c(unsigned char *p)
{
    if (func_0208e484(p + 0x94) != 0) {
        unsigned char v = p[0x1502];
        if (v == 0) {
            goto case0;
        }
        if (v == 1) {
            goto case1;
        }
        if (v != 2) {
            goto end;
        }
        func_ov132_0229b0d0(p);
        goto end;
    case0:
        func_ov132_0229aff8((char *) p);
        goto end;
    case1:
        func_ov132_0229af88((void *) p);
    end:;
    }
}

void func_ov132_0229b214(void *self)
{
    if (func_0208e484((unsigned char *) ((char *) self + 0x94)) != 0) {
        func_ov132_0229adfc(self);
        func_ov002_02208098(self, ((unsigned char *) self)[0x1503]);
    }
}

void func_ov132_0229b1b0(unsigned char *base)
{
    if (func_ov002_0220a700(base + 0xf8)) {
        if (func_0208e4bc(base + 0x94)) {
            int a;
            int b;
            int c;

            a = func_ov002_0220a6e0(base + 0xf8);
            b = func_ov002_0220a768(base + 0xf8, -1);
            c = func_ov002_0220a72c(base + 0xf8, -1);
            base += 0x94;
            func_ov002_0220a0b4(base, a + b, a + c);
        }
    } else {
        func_ov132_0229ae90((void *) base);
        func_ov002_022080a0(base, 1);
    }
}

void func_ov132_0229b184(unsigned char *self)
{
    if (self[0x1506]) {
        self[0x1506] = self[0x1506] - 1;
    } else {
        func_ov132_0229ae90(self);
        func_ov002_022080a0((unsigned char *) self, 1);
    }
}

void func_ov132_0229b158(char *p)
{
    if (func_ov002_0220b8ac(p + 0x3e4, 0)) {
        func_ov132_0229b104((int) p);
        p += 0x94;
        func_0208e5cc(p);
    }
}

int func_ov132_0229b140(void *p)
{
    func_ov132_0229ae90(p);
    return (int) func_ov002_02208098(p, 0);
}

int func_ov132_0229b124(void *a)
{
    func_ov132_0229af04((UnkStruct_0229af04 *) a);
    func_ov002_02207fc0(a);
    return (int) func_ov002_02208098(a, 1);
}

void func_ov132_0229b104(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov132_0229b140((void *) r4);
    } else {
        func_ov132_0229b124((void *) r4);
    }
}

void func_ov132_0229b0d0(unsigned char *p)
{
    p[0x1505] = 0x44;
    func_0206fc4c(0);
    func_ov002_0220a720(p + 0xf8, 6);
    func_ov002_02208090(p, 2);
    func_ov002_02208098((void *) p, 5);
}

void func_ov132_0229b068(void *base)
{
    func_ov002_02208090((unsigned char *) base, 2);
    *((unsigned char *) ((char *) base + 0x1506)) = 10;
    func_020b9bbc((char *) base + 0x39c, (char *) base + 0x500, 6, 0x800, 0);
    func_020b9bbc((char *) base + 0x3c0, (char *) base + 0xd00, 4, 0x800, 0);
    func_ov002_02208098(base, 6);
    func_0200467c(0x29);
}

void func_ov132_0229aff8(char *arg)
{
    if (func_020983f0((int *) func_020992fc((int) func_020984e8())) == 0x3b9ac9ff) {
        func_ov132_0229af54((void *) arg, 14);
        return;
    }
    arg[0x1505] = 0x35;
    func_0206fdd4(arg + 0x500, 6, 7, 0x19, 10, 7);
    func_0206fdd4(arg + 0xd00, 6, 7, 0x19, 10, 7);
    func_ov132_0229b068((void *) arg);
}

void func_ov132_0229af88(void *param)
{
    if (func_02098cc0(func_02099734((int) func_020984e8()), 1, 0) == 0) {
        func_ov132_0229af54(param, 0xf);
        return;
    } else {
        ((char *) param)[0x1505] = 0x36;
        func_0206fdd4((char *) ((char *) param + 0x500), 6, 0xc, 0x19, 0xf, 7);
        func_0206fdd4((char *) ((char *) param + 0xd00), 6, 0xc, 0x19, 0xf, 7);
        func_ov132_0229b068(param);
    }
}

void func_ov132_0229af54(void *r0, unsigned char r1)
{
    unsigned char local;
    void *r4 = r0;

    local = r1;
    func_ov002_0220b9b8((char *) r4 + 0x3e4, &local, 1, 0);
    func_ov002_02208098(r4, 7);
    func_0208e5c4((char *) r4 + 0x94);
}

void func_ov132_0229af04(UnkStruct_0229af04 *p)
{
    int a = (int) func_ov132_0229aed8(p);
    int b = func_ov132_0229aeac((struct UnkStruct_0229aeac *) p);
    func_ov002_0220a0b4((unsigned char *) (&p->sub), a, b);
    if (p->flag == 2) {
        func_ov002_0220a374(&p->sub, 7);
    } else {
        func_ov002_0220a374(&p->sub, 1);
    }
    func_ov132_0229adfc(p);
}

void *func_ov132_0229aed8(void *self)
{
    unsigned char idx = ((unsigned char *) self)[0x1502];
    if (idx == 2) {
        return (void *) func_ov002_0220a768((unsigned char *) ((char *) self + 0xf8), 6);
    }
    return data_ov132_0229b904[idx];
}

int func_ov132_0229aeac(struct UnkStruct_0229aeac *obj)
{
    if (obj->flag == 2) {
        return func_ov002_0220a72c((unsigned char *) ((char *) obj + 0xf8), 6);
    } else {
        return data_ov132_0229b910[obj->flag];
    }
}
