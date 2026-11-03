/* letter_pick: 14 functions, module ov108
 * mwccarm 1.2/base -O4,s
 * func_ov108_0229c5b4 @ 0x0229c5b4, 0x20 bytes, Thumb
 * func_ov108_0229c578 @ 0x0229c578, 0x3c bytes, Thumb
 * func_ov108_0229c52c @ 0x0229c52c, 0x4c bytes, Thumb
 * func_ov108_0229c508 @ 0x0229c508, 0x24 bytes, Thumb
 * func_ov108_0229c498 @ 0x0229c498, 0x70 bytes, Thumb
 * func_ov108_0229c468 @ 0x0229c468, 0x30 bytes, Thumb
 * func_ov108_0229c404 @ 0x0229c404, 0x64 bytes, Thumb
 * func_ov108_0229c358 @ 0x0229c358, 0xac bytes, Thumb
 * func_ov108_0229c2f0 @ 0x0229c2f0, 0x68 bytes, Thumb
 * func_ov108_0229c2dc @ 0x0229c2dc, 0x12 bytes, Thumb
 * func_ov108_0229c2cc @ 0x0229c2cc, 0xe bytes, Thumb
 * func_ov108_0229c2bc @ 0x0229c2bc, 0xe bytes, Thumb
 * func_ov108_0229c21c @ 0x0229c21c, 0xa0 bytes, Thumb
 * func_ov108_0229c180 @ 0x0229c180, 0x9c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x2b4];
    unsigned char flag;
} UnkStruct_0229c508;

typedef struct {
    unsigned char pad_00[0x2b0];
    unsigned char unk_2B0;
} UnkStruct_0229c2f0;

struct Unknown_0229c2dc {
    char pad_00[0x94];
    unsigned int unk_94;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a374(int, int);
extern int func_ov002_02207d24(void *p, int n);
extern void func_ov108_0229cdb8(UnkStruct_0229c508 *self);
extern void func_ov108_0229cf4c(UnkStruct_0229c508 *self);
extern void func_ov002_02208c58(void *p, void *q, int n);
extern int func_ov108_0229cc20(unsigned char *a, unsigned char b);
extern int func_ov108_0229cbe4(unsigned char *a, unsigned char b);
extern void func_ov002_02209874(void *p, void *q);
extern void func_ov002_02209910(void *p, int v, int w);
extern void func_ov002_0220970c(void *p, int n);
extern void func_ov108_0229c5f4(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_ov108_0229cc5c(void *p, int a);
extern void func_ov108_0229c794(void *p);
extern void func_ov002_02208d30(void *p, int a);
extern int func_ov002_02208d4c(void *p, int a, int b);
extern int func_ov002_022088ac(void *arg);
extern int func_ov002_0220889c(void *arg);
extern int func_ov002_022088cc(void *arg);
extern int func_ov002_022088bc(void *arg);
extern int func_ov108_0229cd70(void *self, int val);
extern char data_ov108_0229e098[];
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_0220ba0c(void *p);
extern void *func_ov002_02209ac8(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void *func_ov002_02207e28(void *p);
extern void *func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void *func_ov094_0229afe0(void *p);
extern void func_02066688(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);

int func_ov108_0229c2dc(struct Unknown_0229c2dc *p, unsigned int mask);
void func_ov108_0229c2bc(void *param0, unsigned int param1);

void func_ov108_0229c5b4(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x2498);
    func_ov002_02208098((void *) (self), 0xb);
}

void func_ov108_0229c578(int *param1, unsigned char param2)
{
    func_ov002_02207d24((void *) ((int) ((char *) param1 + 0x23b0)), 1);
    *(unsigned char *) ((char *) param1 + 0x2b2) = param2;
    func_ov002_0220a374((int) ((char *) param1 + 0x2498), 5);
    func_ov002_02208098((void *) ((int) param1), 0xf);
}

void func_ov108_0229c52c(unsigned char *self, unsigned char param)
{
    unsigned char b;
    func_ov002_02207d24(self + 0x23b0, 1);
    b = self[0x8d];
    self[0x2b3] = b;
    self[0x2b2] = param;
    func_ov002_0220a374((int) (self + 0x2498), 6);
    func_ov002_02208098((void *) (self), 16);
}

void func_ov108_0229c508(UnkStruct_0229c508 *self)
{
    switch (self->flag) {
        case 0:
            func_ov108_0229cdb8(self);
            break;
        case 1:
        default:
            func_ov108_0229cf4c(self);
            break;
    }
}

void func_ov108_0229c498(unsigned char *a, int flag)
{
    int v;
    int w;

    func_ov002_02208c58(a + 0x24fc, a + 0x28e4, 0);
    v = func_ov108_0229cc20(a, a[0x2b1]);
    w = func_ov108_0229cbe4(a, a[0x2b1]);
    if (flag) {
        func_ov002_02209874(a + 0x24fc, a + 0x23b0);
    } else {
        func_ov002_02209910(a + 0x24fc, v, w);
    }
    func_ov002_0220970c(a + 0x24fc, 0);
    func_ov002_02208098((void *) (a), 0x13);
}

void func_ov108_0229c468(void *p)
{
    *((unsigned char *) p + 0x2b4) = 1;
    func_ov108_0229c5f4(p);
    func_ov002_022096d8((char *) p + 0x24fc, 0);
    func_ov002_02208098((void *) (p), 0x15);
}

void func_ov108_0229c404(void *self, int a, int b)
{
    char *base = (char *) self;
    base[0x2b1] = (char) a;
    func_ov002_02208d30(base + 0x28e4, 1);
    func_ov108_0229cc5c(self, a);
    func_ov002_02208d4c(base + 0x28e4, 0xd, 0);
    func_ov002_02208d4c(base + 0x28e4, 2, 1);
    func_ov108_0229c794(self);
    if (b == 0) {
        func_ov002_02207d24(base + 0x23b0, 1);
    }
    func_ov108_0229c498((unsigned char *) self, b);
}

void func_ov108_0229c358(unsigned char *self, void *arg, int flag)
{
    int r4;
    int r6;

    r4 = self[0x2b0] - 11;
    r6 = r4 >> 1;

    if (func_ov002_022088ac(arg) != 0) {
        if ((r4 & 1) > 0) {
            self[0x2b0]--;
        }
    } else {
        if (func_ov002_0220889c(arg) != 0) {
            if ((r4 & 1) < 1) {
                self[0x2b0]++;
            }
        }
    }

    if (func_ov108_0229cd70(self, self[0x2b0]) != 0) {
        if (func_ov108_0229c2dc((struct Unknown_0229c2dc *) self, 0x30) == 0) {
            if (func_ov002_022088cc(arg) != 0) {
                if (r6 > 0) {
                    self[0x2b0] -= 2;
                }
            } else {
                if (func_ov002_022088bc(arg) != 0) {
                    if (r6 < 4) {
                        self[0x2b0] += 2;
                    } else {
                        self[0x2b0] = 0x15;
                    }
                }
            }
        }
    }
}

int func_ov108_0229c2f0(UnkStruct_0229c2f0 *obj, int a, int b)
{
    unsigned char init = obj->unk_2B0;
    func_ov108_0229c2bc(obj, 0x30);
    if (a == 0) {
        return 0;
    }
    if (func_ov108_0229cd70(obj, (unsigned char) obj->unk_2B0) != 0) {
        func_ov108_0229c358((unsigned char *) obj, (void *) a, b);
    } else {
        if (obj->unk_2B0 == 0x15) {
            if (func_ov002_022088cc((void *) a) != 0) {
                obj->unk_2B0 = 0x13;
            }
        }
    }
    if (init != obj->unk_2B0) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov108_0229c2dc(struct Unknown_0229c2dc *p, unsigned int mask)
{
    if ((p->unk_94 & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov108_0229c2cc(void *r0, int r1)
{
    *(unsigned int *) ((char *) r0 + 0x94) |= r1;
}

void func_ov108_0229c2bc(void *param0, unsigned int param1)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) param0 + 0x94);
    val = *ptr;
    val &= ~param1;
    *((unsigned int *) ((char *) param0 + 0x94)) = val;
}

void *func_ov108_0229c21c(void *obj)
{
    *(void **) obj = data_ov108_0229e098;
    func_ov002_0220afdc((char *) obj + 0x2a0c);
    func_ov002_0220ba0c((char *) obj + 0x28f0);
    func_ov002_02209ac8((char *) obj + 0x24fc);
    func_ov002_02209cb4((char *) obj + 0x2498);
    func_ov002_02209e38((char *) obj + 0x2480);
    func_ov002_02207e28((char *) obj + 0x23b0);
    func_ov094_0229a2d0((char *) obj + 0x0d78);
    func_ov094_0229bc30((char *) obj + 0x0d50);
    func_ov094_0229afe0((char *) obj + 0x02f0);
    func_02066688((char *) obj + 0x01ac);
    func_02066688((char *) obj + 0xac);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}

void *func_ov108_0229c180(void *self)
{
    *(void **) self = ((char *) data_ov108_0229e098);
    func_ov002_0220afdc((char *) self + 0x2a0c);
    func_ov002_0220ba0c((char *) self + 0x28f0);
    func_ov002_02209ac8((char *) self + 0x24fc);
    func_ov002_02209cb4((char *) self + 0x2498);
    func_ov002_02209e38((char *) self + 0x2480);
    func_ov002_02207e28((char *) self + 0x23b0);
    func_ov094_0229a2d0((char *) self + 0x0d78);
    func_ov094_0229bc30((char *) self + 0x0d50);
    func_ov094_0229afe0((char *) self + 0x02f0);
    func_02066688((char *) self + 0x01ac);
    func_02066688((char *) self + 0xac);
    func_ov002_0220826c(self);
    return self;
}
