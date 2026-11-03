/* villager_mode_record: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209c108 @ 0x0209c108, 0x60 bytes, Thumb
 * func_0209c0a0 @ 0x0209c0a0, 0x68 bytes, Thumb
 * func_0209c020 @ 0x0209c020, 0x80 bytes, Thumb
 * func_0209bff0 @ 0x0209bff0, 0x30 bytes, Thumb
 * func_0209bfec @ 0x0209bfec, 0x2 bytes, Thumb
 * func_0209bfe8 @ 0x0209bfe8, 0x4 bytes, Thumb
 * func_0209bf80 @ 0x0209bf80, 0x68 bytes, Thumb
 * func_0209bf28 @ 0x0209bf28, 0x56 bytes, Thumb
 */

struct UnkStruct_0209c0a0 {
    unsigned char unk_00[3];
    unsigned char unk_03;
    unsigned char unk_04[4];
    unsigned char unk_08[8];
    unsigned char unk_10;
    unsigned char unk_11[16];
    unsigned char unk_21;
};

struct UnkStruct_0209c020 {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned char unk_11[0x10];
    unsigned char b0 : 1;
};

extern int func_0209c4a8(unsigned char *);
extern int func_0209c38c(int);
extern void func_0209c32c(unsigned char *, int);
extern void func_0209c470(unsigned char *, int);
extern void func_0209e474(unsigned char *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0209e3ac(void *a, void *b, int n);
extern int func_0209e380(void *a, void *b);
extern int func_020b4a20(void *self, unsigned char *p, void *g);
extern char data_020e35cc;
extern unsigned char func_0209c410(unsigned char *p, unsigned char c);
extern void func_0209c448(unsigned char *p, unsigned char a, unsigned char b);
extern void func_0209c52c(unsigned char *p);
extern unsigned char data_020d1a38[];
extern int func_020644cc(int n);

int func_0209c108(unsigned char *p)
{
    int r4;

    if (p[0x10] != 8) {
        goto fail;
    }
    r4 = func_0209c4a8(p + 0x11);
    if (func_0209c38c(r4) == 0) {
        goto fail;
    }
    func_0209c32c(p, r4);
    func_0209c470(p + 0x11, r4);
    p[0x21] &= ~1;
    func_0209e474(p);
    MI_CpuCopy8(p, p + 8, 8);
    return r4;
fail:
    return 0xc;
}

int func_0209c0a0(struct UnkStruct_0209c0a0 *self, unsigned char *other)
{
    int x;

    if (self->unk_10 != 0xb) {
        goto fail;
    }
    if (other[3] == self->unk_03) {
        goto fail;
    }

    x = func_0209c4a8((unsigned char *) self->unk_11);
    if (func_0209c38c(x) == 0) {
        goto fail;
    }

    func_0209c32c((unsigned char *) self, x);
    func_0209c470((unsigned char *) self->unk_11, x);
    self->unk_21 &= ~1;
    func_0209e474((unsigned char *) self);
    MI_CpuCopy8(self, self->unk_08, 8);

    return x;

fail:
    return 0xc;
}

int func_0209c020(struct UnkStruct_0209c020 *obj, void *b)
{
    if (obj->unk_10 == 0xa) {
        if (b == 0 || (func_0209e3ac(b, obj, 0x3f) == 1 && func_0209e380(obj, b) >= 1)) {
            b = (void *) func_0209c4a8((unsigned char *) obj->unk_11);
            if (func_0209c38c((unsigned int) b) != 0) {
                func_0209c32c((unsigned char *) obj, (int) b);
                func_0209c470((unsigned char *) obj->unk_11, (int) b);
                obj->b0 = 0;
                func_0209e474((unsigned char *) obj);
                MI_CpuCopy8((void *) obj, (char *) obj + 8, 8);
                return (int) b;
            }
        }
    }
    return 0xc;
}

int func_0209bff0(void *self, int b)
{
    int temp;
    unsigned char v;
    if (func_0209c38c(b)) {
        temp = b;
    } else {
        temp = 7;
    }
    v = (unsigned char) temp;
    return func_020b4a20(self, &v, &data_020e35cc);
}

void *func_0209bfec(void *record)
{
    return record;
}

int func_0209bfe8(int p0)
{
    return ((int) (p0) + (8));
}

void func_0209bf80(unsigned char *base, short *arr)
{
    unsigned char *gp = (unsigned char *) data_020d1a38;
    int k = 0;
    int i;
    for (i = 0; i < 8; i++) {
        int r = func_0209c410(base + 0x19, (unsigned char) i);
        if (*gp != 0 && r != 0) {
            short val = arr[k];
            int t = (val * *gp * r) >> 12;
            func_0209c448(base + 0x11, (unsigned char) i, (unsigned char) t);
        }
        arr++;
        gp++;
    }
    func_0209c52c(base + 0x19);
}

int func_0209bf28(unsigned char *base, short *arr)
{
    int found = 0;
    int idx;
    int v;

    for (idx = 0; idx < 8; idx++) {
        if (func_0209c410(base + 0x11, idx) < 0xff) {
            v = func_020644cc(10);
            if (v > 0) {
                func_0209c448(base + 0x11, idx, (*arr * v) >> 12);
            }
            found = 1;
        }
        arr++;
    }
    return found;
}
