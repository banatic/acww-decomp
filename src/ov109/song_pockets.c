/* song_pockets: 16 functions, module ov109
 * mwccarm 1.2/base -O4,s
 * func_ov109_0229c638 @ 0x0229c638, 0x20 bytes, Thumb
 * func_ov109_0229c5d4 @ 0x0229c5d4, 0x64 bytes, Thumb
 * func_ov109_0229c564 @ 0x0229c564, 0x70 bytes, Thumb
 * func_ov109_0229c534 @ 0x0229c534, 0x30 bytes, Thumb
 * func_ov109_0229c4f4 @ 0x0229c4f4, 0x40 bytes, Thumb
 * func_ov109_0229c4cc @ 0x0229c4cc, 0x28 bytes, Thumb
 * func_ov109_0229c498 @ 0x0229c498, 0x34 bytes, Thumb
 * func_ov109_0229c470 @ 0x0229c470, 0x28 bytes, Thumb
 * func_ov109_0229c418 @ 0x0229c418, 0x58 bytes, Thumb
 * func_ov109_0229c330 @ 0x0229c330, 0xe8 bytes, Thumb
 * func_ov109_0229c2c4 @ 0x0229c2c4, 0x6c bytes, Thumb
 * func_ov109_0229c2ac @ 0x0229c2ac, 0x18 bytes, Thumb
 * func_ov109_0229c29c @ 0x0229c29c, 0x10 bytes, Thumb
 * func_ov109_0229c28c @ 0x0229c28c, 0x10 bytes, Thumb
 * func_ov109_0229c204 @ 0x0229c204, 0x88 bytes, Thumb
 * func_ov109_0229c180 @ 0x0229c180, 0x84 bytes, Thumb
 */

struct UnkStruct_0229c5d4 {
    char pad_00[0x29d4];
    unsigned char unk_29D4;
    char pad_29D5[2];
    unsigned char unk_29D7;
};

typedef struct {
    unsigned char pad_00[0x218c];
    unsigned char unk_218C;
    unsigned char pad_218D[0x533];
    unsigned char unk_26C0;
    unsigned char pad_26C1[0x313];
    unsigned char unk_29D4;
} UnkStruct_0229c418;

typedef struct Other Other;

struct UnkStruct_0229c330 {
    unsigned char pad_00[0x29d3];
    unsigned char unk_29D3;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov109_0229ca7c(void *self, unsigned char byte);
extern int func_02060a34(unsigned int arg0);
extern void func_ov109_0229cccc(void *self, int num);
extern void func_020609dc(int result);
extern void func_ov109_0229cc0c(void *self, unsigned char byte, int constant, int zero);
extern void func_ov109_0229cd9c(void *self);
extern void func_ov002_02208c58(void *p, void *q, int n);
extern int func_ov109_0229cbd4(unsigned char *a, unsigned char b);
extern int func_ov109_0229cb9c(unsigned char *a, unsigned char b);
extern void func_ov002_02209874(void *p, void *q);
extern void func_ov002_02209910(void *p, int v, int w);
extern void func_ov002_0220970c(void *p, int n);
extern void func_ov109_0229c678(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_0206fc80(unsigned char);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov109_0229c828(void *);
extern void *func_ov002_0220a720(char *, int);
extern void func_0200467c(int);
extern int func_ov002_02208d4c(void *ptr, int a, int b);
extern void func_ov002_02208d30(void *addr, int val);
extern int func_ov109_0229ccb4(void *self, int param2);
extern int func_ov002_022088ac(Other *p);
extern int func_ov002_022088cc(Other *p);
extern int func_ov002_0220889c(Other *p);
extern int func_ov002_022088bc(Other *p);
extern void func_ov002_0220a314(void *addr);
extern void func_ov002_0220a2b4(void *p);
extern void *func_ov002_0220afdc(void *);
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
extern unsigned char data_ov109_0229dbd8[];

void func_ov109_0229c4f4(void *self);
int func_ov109_0229c2ac(void *ptr, int mask);
void func_ov109_0229c29c(void *p, unsigned int mask);
void func_ov109_0229c28c(unsigned int *base, unsigned int mask);

void func_ov109_0229c638(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x2274);
    func_ov002_02208098(arg0, 9);
}

void func_ov109_0229c5d4(struct UnkStruct_0229c5d4 *self)
{
    switch (self->unk_29D7) {
        case 0: {
            int result;
            result = func_ov109_0229ca7c(self, self->unk_29D4);
            if (func_02060a34(result) != 0) {
                func_ov109_0229cccc(self, 17);
            } else {
                func_020609dc(result);
                func_ov109_0229cc0c(self, self->unk_29D4, 0xfff1, 0);
                func_ov109_0229c4f4(self);
            }
            break;
        }
        case 1:
        default:
            func_ov109_0229cd9c(self);
            break;
    }
}

void func_ov109_0229c564(unsigned char *a, int flag)
{
    int v;
    int w;

    func_ov002_02208c58(a + 0x22d8, a + 0x26c0, 0);
    v = func_ov109_0229cbd4(a, a[0x29d4]);
    w = func_ov109_0229cb9c(a, a[0x29d4]);
    if (flag) {
        func_ov002_02209874(a + 0x22d8, a + 0x218c);
    } else {
        func_ov002_02209910(a + 0x22d8, v, w);
    }
    func_ov002_0220970c(a + 0x22d8, 0);
    func_ov002_02208098(a, 0xb);
}

void func_ov109_0229c534(void *self)
{
    *(unsigned char *) ((char *) self + 0x29d7) = 1;
    func_ov109_0229c678(self);
    func_ov002_022096d8((char *) self + 0x22d8, 0);
    func_ov002_02208098(self, 0xd);
}

void func_ov109_0229c4f4(void *self)
{
    func_0206fc80(((unsigned char *) self)[0x29d4]);
    func_0206fc4c(1);
    ((unsigned char *) self)[0x8c] = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x218c, 1);
    func_ov109_0229c828(self);
}

void func_ov109_0229c4cc(char *s)
{
    func_ov002_0220a720(s + 0x27e8, 9);
    func_ov002_02208098((void *) s, 0xf);
    func_0200467c(0x28);
}

void func_ov109_0229c498(void *self)
{
    func_0206fc4c(0);
    *(unsigned char *) ((char *) self + 0x8c) = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x218c, 1);
    func_ov109_0229c828(self);
}

void func_ov109_0229c470(void *obj)
{
    char *base = (char *) obj;
    func_ov002_02208d4c(base + 0x26c0, 0x73, 0);
    func_ov002_02208d4c(base + 0x26c0, 2, 1);
}

void func_ov109_0229c418(UnkStruct_0229c418 *self, unsigned char param2, int param3)
{
    self->unk_29D4 = param2;
    func_ov002_02208d30((void *) &self->unk_26C0, 1);
    if (func_ov109_0229ccb4(self, param2) != 0) {
        func_ov109_0229c470(self);
        func_ov109_0229c828(self);
        if (param3 == 0) {
            func_ov002_02207d24((void *) &self->unk_218C, 1);
        }
        func_ov109_0229c564((unsigned char *) self, param3);
    }
}

void func_ov109_0229c330(struct UnkStruct_0229c330 *self, Other *other)
{
    int field;
    int count;

    field = self->unk_29D3;
    count = 0;
    while (field >= 5) {
        field -= 5;
        count++;
    }

    if (func_ov002_022088ac(other)) {
        if (func_ov002_022088cc(other) && count != 0) {
            goto out;
        }
        if (field == 0) {
            self->unk_29D3 += 4;
            func_ov109_0229c29c((void *) self, 8);
        } else {
            self->unk_29D3 -= 1;
        }
    } else if (func_ov002_0220889c(other) && !func_ov002_022088bc(other)) {
        if (field == 4) {
            self->unk_29D3 -= 4;
            func_ov109_0229c29c((void *) self, 0x10);
        } else {
            self->unk_29D3 += 1;
        }
    }

out:
    if (func_ov109_0229c2ac((void *) self, 0x18) != 0) {
        return;
    }

    if (func_ov002_022088cc(other)) {
        if (count > 0) {
            self->unk_29D3 -= 5;
        }
        return;
    }

    if (func_ov002_022088bc(other)) {
        if (count < 2) {
            self->unk_29D3 += 5;
        } else {
            self->unk_29D3 = 15;
            func_ov002_0220a314((char *) self + 0x2274);
        }
        return;
    }
}

int func_ov109_0229c2c4(unsigned char *p, int a)
{
    unsigned char old = *(p + 0x29d3);
    func_ov109_0229c28c((unsigned int *) p, 0x18);
    if (a == 0) {
        return 0;
    }

    if (func_ov109_0229ccb4(p, (unsigned char) (*(p + 0x29d3)))) {
        func_ov109_0229c330((struct UnkStruct_0229c330 *) p, (Other *) a);
    } else {
        if (*(p + 0x29d3) == 0xf) {
            if (func_ov002_022088cc((Other *) a)) {
                *(p + 0x29d3) = 0xe;
                func_ov002_0220a2b4(p + 0x2274);
            }
        }
    }

    if (old == *(p + 0x29d3)) {
        return 0;
    } else {
        return 1;
    }
}

int func_ov109_0229c2ac(void *ptr, int mask)
{
    if (*(int *) ((char *) ptr + 0x29b4) & mask) {
        return 1;
    }
    return 0;
}

void func_ov109_0229c29c(void *p, unsigned int mask)
{
    *(unsigned int *) ((char *) p + 0x29b4) |= mask;
}

void func_ov109_0229c28c(unsigned int *base, unsigned int mask)
{
    base = (unsigned int *) ((char *) base + 0x29b4);
    *base &= ~mask;
}

void *func_ov109_0229c204(void *obj)
{
    char *base = (char *) obj;
    *((void **) base) = (void *) ((char *) data_ov109_0229dbd8);
    func_ov002_0220afdc((void *) (base + 0x27e8));
    func_ov002_0220ba0c((void *) (base + 0x26cc));
    func_ov002_02209ac8((void *) (base + 0x22d8));
    func_ov002_02209cb4((void *) (base + 0x2274));
    func_ov002_02209e38((void *) (base + 0x225c));
    func_ov002_02207e28((void *) (base + 0x218c));
    func_ov094_0229a2d0((void *) (base + 0x0b54));
    func_ov094_0229bc30((void *) (base + 0x0b2c));
    func_ov094_0229afe0((void *) (base + 0xcc));
    func_ov002_0220826c((void *) base);
    func_ov002_02207f6c((void *) base);
    return obj;
}

void *func_ov109_0229c180(void *obj)
{
    *(void **) obj = (void *) data_ov109_0229dbd8;
    func_ov002_0220afdc((char *) obj + 0x27e8);
    func_ov002_0220ba0c((char *) obj + 0x26cc);
    func_ov002_02209ac8((char *) obj + 0x22d8);
    func_ov002_02209cb4((char *) obj + 0x2274);
    func_ov002_02209e38((char *) obj + 0x225c);
    func_ov002_02207e28((char *) obj + 0x218c);
    func_ov094_0229a2d0((char *) obj + 0x0b54);
    func_ov094_0229bc30((char *) obj + 0x0b2c);
    func_ov094_0229afe0((char *) obj + 0x0cc);
    func_ov002_0220826c(obj);
    return obj;
}
