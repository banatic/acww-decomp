/* pockets_view: 16 functions, module ov099
 * mwccarm 1.2/base -O4,s
 * func_ov099_0229c5c8 @ 0x0229c5c8, 0x20 bytes, Thumb
 * func_ov099_0229c5a8 @ 0x0229c5a8, 0x20 bytes, Thumb
 * func_ov099_0229c56c @ 0x0229c56c, 0x3c bytes, Thumb
 * func_ov099_0229c520 @ 0x0229c520, 0x4c bytes, Thumb
 * func_ov099_0229c4fc @ 0x0229c4fc, 0x24 bytes, Thumb
 * func_ov099_0229c4a0 @ 0x0229c4a0, 0x5c bytes, Thumb
 * func_ov099_0229c470 @ 0x0229c470, 0x30 bytes, Thumb
 * func_ov099_0229c434 @ 0x0229c434, 0x3c bytes, Thumb
 * func_ov099_0229c3e0 @ 0x0229c3e0, 0x54 bytes, Thumb
 * func_ov099_0229c30c @ 0x0229c30c, 0xd4 bytes, Thumb
 * func_ov099_0229c2c4 @ 0x0229c2c4, 0x48 bytes, Thumb
 * func_ov099_0229c2ac @ 0x0229c2ac, 0x18 bytes, Thumb
 * func_ov099_0229c29c @ 0x0229c29c, 0x10 bytes, Thumb
 * func_ov099_0229c28c @ 0x0229c28c, 0x10 bytes, Thumb
 * func_ov099_0229c204 @ 0x0229c204, 0x88 bytes, Thumb
 * func_ov099_0229c180 @ 0x0229c180, 0x84 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x290b];
    unsigned char flag;
} UnkStruct_0229c4fc;

extern void func_ov002_0220a164(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a374(void *p, int n);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov099_0229d0f0(UnkStruct_0229c4fc *self);
extern int func_ov099_0229cd70(void *p, int b);
extern int func_ov099_0229cd1c(void *p, int b);
extern void func_ov002_02208c58(void *a, void *b, int c);
extern void func_ov002_02209910(void *a, int b, int c);
extern void func_ov002_0220970c(void *a, int b);
extern void func_ov099_0229c608(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_0206fe54(void);
extern int func_ov002_02208d4c(char *, int, int);
extern void func_ov002_02208d30(void *ptr, int flag);
extern int func_ov099_0229cf30(unsigned char *ptr, unsigned char val);
extern void func_ov099_0229c754(unsigned char *ptr);
extern int func_ov002_022088ac(void *arg);
extern int func_ov002_022088cc(void *arg);
extern int func_ov002_0220889c(void *arg);
extern int func_ov002_022088bc(void *arg);
extern int data_ov099_0229e040;
extern void func_02066688(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

int func_ov099_0229c2ac(void *self, int mask);
void func_ov099_0229c29c(unsigned int *base, unsigned int mask);
void func_ov099_0229c28c(unsigned int *base, unsigned int mask);

void func_ov099_0229c5c8(void *arg0)
{
    func_ov002_0220a164((char *) arg0 + 0x2274);
    func_ov002_02208098(arg0, 10);
}

void func_ov099_0229c5a8(void *p)
{
    func_ov002_0220a374((char *) p + 0x2274, 4);
    func_ov002_02208098(p, 0xb);
}

void func_ov099_0229c56c(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x218c, 1);
    ((char *) self)[0x2909] = val;
    func_ov002_0220a374((char *) self + 0x2274, 5);
    func_ov002_02208098(self, 0xd);
}

void func_ov099_0229c520(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    int r0_2;
    int r1_2;
    int r0_3;
    int r1_3;
    int r0_4;
    int r1_4;

    r0_2 = r5 + 0x218c;
    r1_2 = 1;
    func_ov002_02207d24((void *) r0_2, r1_2);

    r0_3 = r5 + 0x8d;
    r1_3 = *(unsigned char *) r0_3;
    r0_4 = r5 + 0x290a;
    *(unsigned char *) r0_4 = r1_3;

    r0_4 = r5 + 0x2909;
    *(unsigned char *) r0_4 = r4;

    r0_4 = r5 + 0x2274;
    r1_4 = 6;
    func_ov002_0220a374((void *) r0_4, r1_4);

    r0_4 = r5 + 0;
    r1_4 = 0xe;
    func_ov002_02208098((void *) r0_4, r1_4);
}

void func_ov099_0229c4fc(UnkStruct_0229c4fc *self)
{
    switch (self->flag) {
        case 0:
            func_ov099_0229c5a8((void *) self);
            break;
        case 1:
        default:
            func_ov099_0229d0f0(self);
            break;
    }
}

void func_ov099_0229c4a0(unsigned char *p)
{
    int v1;
    int v2;

    func_ov002_02208c58(p + 0x22d8, p + 0x26c0, 0);
    v1 = func_ov099_0229cd70(p, p[0x2908]);
    v2 = func_ov099_0229cd1c(p, p[0x2908]);
    func_ov002_02209910(p + 0x22d8, v1, v2);
    func_ov002_0220970c(p + 0x22d8, 0);
    func_ov002_02208098(p, 0x11);
}

void func_ov099_0229c470(void *param)
{
    char *p = (char *) param;
    p[0x290b] = 1;
    func_ov099_0229c608(param);
    func_ov002_022096d8((char *) param + 0x22d8, 0);
    func_ov002_02208098(param, 0x13);
}

void func_ov099_0229c434(char *param)
{
    if (func_0206fe54()) {
        func_ov002_02208d4c(param + 0x26c0, 0, 0);
    }
    func_ov002_02208d4c(param + 0x26c0, 1, 1);
    func_ov002_02208d4c(param + 0x26c0, 2, 1);
}

void func_ov099_0229c3e0(unsigned char *ptr, unsigned char val)
{
    ptr[0x2908] = val;
    func_ov002_02208d30(ptr + 0x26c0, 1);
    if (func_ov099_0229cf30(ptr, val)) {
        func_ov099_0229c434((char *) ptr);
        func_ov099_0229c754(ptr);
        func_ov002_02207d24(ptr + 0x218c, 1);
        func_ov099_0229c4a0(ptr);
    }
}

void func_ov099_0229c30c(unsigned char *obj, void *arg)
{
    int b;
    int q;

    b = obj[0x2907];
    q = 0;
    while (b >= 5) {
        b -= 5;
        q++;
    }

    if (func_ov002_022088ac(arg)) {
        if (func_ov002_022088cc(arg) && q != 0) {
            goto exit;
        }
        if (b == 0) {
            obj[0x2907] += 4;
            func_ov099_0229c29c((unsigned int *) obj, 0x10);
        } else {
            obj[0x2907] -= 1;
        }
    } else {
        if (func_ov002_0220889c(arg)) {
            if (func_ov002_022088bc(arg) == 0) {
                if (b == 4) {
                    obj[0x2907] -= 4;
                    func_ov099_0229c29c((unsigned int *) obj, 0x20);
                } else {
                    obj[0x2907] += 1;
                }
            }
        }
    }

exit:
    if (func_ov099_0229c2ac((void *) obj, 0x30) == 0) {
        if (func_ov002_022088cc(arg) != 0) {
            if (q > 0) {
                obj[0x2907] -= 5;
            }
        } else {
            if (func_ov002_022088bc(arg) != 0 && q < 2) {
                obj[0x2907] += 5;
            }
        }
    }
}

int func_ov099_0229c2c4(unsigned char *p, int b)
{
    unsigned char v = p[0x2907];
    func_ov099_0229c28c((unsigned int *) p, 0x30);
    if (b == 0) {
        return 0;
    }
    if (func_ov099_0229cf30(p, p[0x2907]) != 0) {
        func_ov099_0229c30c(p, (void *) b);
    }
    return (v == p[0x2907]) ? 0 : 1;
}

int func_ov099_0229c2ac(void *self, int mask)
{
    if (*(unsigned int *) ((char *) self + 0x27e8) & mask) {
        return 1;
    }
    return 0;
}

void func_ov099_0229c29c(unsigned int *base, unsigned int mask)
{
    base[0x9fa] |= mask;
}

void func_ov099_0229c28c(unsigned int *base, unsigned int mask)
{
    *(unsigned int *) ((unsigned char *) base + 0x27e8) &= ~mask;
}

void *func_ov099_0229c204(void *obj)
{
    *(int *) obj = (int) &data_ov099_0229e040;
    func_02066688((char *) obj + 0x2800);
    func_ov002_0220ba0c((char *) obj + 0x26cc);
    func_ov002_02209ac8((char *) obj + 0x22d8);
    func_ov002_02209cb4((char *) obj + 0x2274);
    func_ov002_02209e38((char *) obj + 0x225c);
    func_ov002_02207e28((char *) obj + 0x218c);
    func_ov094_0229a2d0((char *) obj + 0x0b54);
    func_ov094_0229bc30((char *) obj + 0x0b2c);
    func_ov094_0229afe0((char *) obj + 0xcc);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}

void *func_ov099_0229c180(void *self)
{
    *(unsigned int *) self = (unsigned int) ((unsigned int *) &data_ov099_0229e040);
    func_02066688((char *) self + 0x2800);
    func_ov002_0220ba0c((char *) self + 0x26cc);
    func_ov002_02209ac8((char *) self + 0x22d8);
    func_ov002_02209cb4((char *) self + 0x2274);
    func_ov002_02209e38((char *) self + 0x225c);
    func_ov002_02207e28((char *) self + 0x218c);
    func_ov094_0229a2d0((char *) self + 0xb54);
    func_ov094_0229bc30((char *) self + 0xb2c);
    func_ov094_0229afe0((char *) self + 0xcc);
    func_ov002_0220826c(self);
    return self;
}
