/* mystery_cat_2: 15 functions, module ov074
 * mwccarm 1.2/base -O4,s
 * func_ov074_022796f8 @ 0x022796f8, 0x80 bytes, Thumb
 * func_ov074_022796a0 @ 0x022796a0, 0x58 bytes, Thumb
 * func_ov074_02279668 @ 0x02279668, 0x38 bytes, Thumb
 * func_ov074_022795d8 @ 0x022795d8, 0x90 bytes, Thumb
 * func_ov074_0227959c @ 0x0227959c, 0x3a bytes, Thumb
 * func_ov074_0227949c @ 0x0227949c, 0x100 bytes, Thumb
 * func_ov074_02279478 @ 0x02279478, 0x22 bytes, Thumb
 * func_ov074_02279230 @ 0x02279230, 0x248 bytes, Thumb
 * func_ov074_022791e0 @ 0x022791e0, 0x50 bytes, Thumb
 * func_ov074_022791c4 @ 0x022791c4, 0x1c bytes, Thumb
 * func_ov074_022791c0 @ 0x022791c0, 0x4 bytes, Thumb
 * func_ov074_02279194 @ 0x02279194, 0x2c bytes, Thumb
 * func_ov074_02279190 @ 0x02279190, 0x4 bytes, Thumb
 * func_ov074_02279154 @ 0x02279154, 0x3c bytes, Thumb
 * func_ov074_02279150 @ 0x02279150, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_022796f8 {
    char pad_00[0x3b0];
    char unk_3B0;
    char pad_3B1[0x1a7];
    char unk_558;
    char pad_559[0xb];
    char unk_564;
    char pad_565[0xec];
    char unk_651;
} UnkStruct_022796f8;

typedef struct {
    int x;
    int pad_04;
    int y;
} UnkStruct_022796a0;

struct UnkStruct_022795d8 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

typedef struct UnkStruct_02279230 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x564 - 0x3aa];
    char unk_564[0x651 - 0x564];
    unsigned char unk_651;
} UnkStruct_02279230;

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern char data_021fbee8[];
int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
void func_02013c0c(void *a);
void func_0201ad18(void *a, int b, int c, int d, int e, int f, int g, int h);
extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_020e92e8(void *);
extern int FX_MulFunc(int first, int second);
extern void func_0204f7e0(int *, int *);
extern int func_02078e98(int *, int);
extern short FX_SinCosTable_[];
extern int data_021cb5a0;
extern void func_0201af58(void *dst, void *src, int a3, int a4);
extern int func_0201ae8c(void *src);
extern void *func_0201ae40(void *p);
extern int func_0201aff8(void *p, void *self, int flag);
extern int func_0201afc0(void *p);
extern void func_0201af48(void *p);
extern void func_0201afd4(void *p, void *buf);
extern char data_ov074_02279d90;
extern char data_ov074_02279d84;
extern unsigned char func_020e8858(unsigned char *p);
extern int func_02019de8(void *p);
extern int func_0201b354(void *p);
extern int func_0200322c(void *p, int *v);
extern int func_0201c3dc(int a);
extern int func_020644cc(int a);
extern int func_02019e00(void *p);
extern void func_ov074_02279778(UnkStruct_02279230 *self, int a);
extern int *func_0201afd0(void *p);
extern void func_02013c04(char *a);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int a);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov074_022796f8(UnkStruct_022796f8 *self)
{
    self->unk_651 = 0;
    func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_02013c0c(&self->unk_558);
    func_02013c0c(&self->unk_558);
    func_0201ad18(&self->unk_3B0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}

int func_ov074_022796a0(int arg0, UnkStruct_022796a0 *a, UnkStruct_022796a0 *b)
{
    int result = 0;
    int ok2 = 0;
    int ok1 = 0;

    if ((b->x > a->x - 0x10000) && (b->x < a->x + 0x10000)) {
        ok1 = 1;
    }
    if (ok1 && (b->y > a->y - 0x1a000)) {
        ok2 = 1;
    }
    if (ok2 && (b->y < a->y + 0xa000)) {
        result = 1;
    }

    return result;
}

int func_ov074_02279668(void *p)
{
    void *base = (char *) p + 0x5c;
    int result = 0;
    if (data_021c67a4 != 0) {
        int arr[3];
        arr[0] = data_021c67d0[0];
        arr[1] = data_021c67d0[1];
        arr[2] = data_021c67d0[2];
        result = func_ov074_022796a0((int) p, (UnkStruct_022796a0 *) arr, (UnkStruct_022796a0 *) base);
    }
    return result;
}

int func_ov074_022795d8(struct UnkStruct_022795d8 *self, int *out1, int *out2)
{
    int r4;
    int r6;
    int r7;
    int local[3];
    int t1, t2;
    r6 = 0;
    local[0] = r6;
    local[1] = r6;
    local[2] = r6;
    r4 = r6;
    while (r4 < 6) {
        r7 = ((unsigned short) (short) func_020e92e8(&data_021cb5a0) >> 4) << 1;
        t1 = FX_MulFunc(0xc000, FX_SinCosTable_[r7]);
        local[0] = t1 + self->unk_5C;
        t2 = FX_MulFunc(0xc000, FX_SinCosTable_[r7 + 1]);
        local[2] = t2 + self->unk_64;
        func_0204f7e0(local, local);
        if (func_02078e98(local, r6) != 0) {
            *out1 = local[0];
            *out2 = local[2];
            r6 = 1;
            break;
        }
        r4++;
    }
    return r6;
}

int func_ov074_0227959c(void *obj, int *out, int a3)
{
    int local[4];
    int result = 0;
    func_0201af58(local, (char *) obj + 0x5C, a3, *(signed short *) ((char *) obj + 0x94));
    if (func_0201ae8c(local) != 1) {
        out[0] = local[0];
        out[1] = local[1];
        out[2] = local[2];
        result = 1;
    }
    return result;
}

int func_ov074_0227949c(void *self)
{
    void *a = (char *) self + 0x564;
    void *b = (char *) self + 0x350;
    void *c = (char *) self + 0x3a8;
    int kind;
    int result;
    char buf[0xc];

    kind = (int) func_0201ae40(c);
    result = 0;
    if (func_0201aff8(b, self, 1) == 0) {
        if (kind == 1) {
            goto case1;
        }
        if (kind == 2) {
            goto case2;
        }
        if (kind != 3) {
            goto done;
        }
        func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        result = 1;
        goto done;
    case1:
        if (func_ov074_0227959c(self, (int *) buf, (int) (&data_ov074_02279d90))) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    case2:
        if (func_ov074_0227959c(self, (int *) buf, (int) (&data_ov074_02279d84))) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    } else {
        if (func_0201afc0(b)) {
            func_0201af48(b);
        }
    }
done:
    return result;
}

int func_ov074_02279478(void *self)
{
    if (*(int *) ((char *) self + 0x98) != 0) {
        if (func_ov074_0227949c(self)) {
            return 1;
        }
    }
    return 0;
}

static __inline int GetState(UnkStruct_02279230 *self)
{
    return func_02019e00(self->unk_564);
}

int func_ov074_02279230(UnkStruct_02279230 *self)
{
    void *sub;
    int ok;
    int dir;
    int mode;
    int *p;
    int v[3];
    int v2[3];

    sub = self->unk_564;
    ok = func_ov074_02279668((void *) self);
    func_020e8858(&self->unk_651);
    if (ok != 0) {
        if (func_ov074_02279478((void *) self) == 0) {
            if (func_02019de8(sub) != 0) {
                if (func_0201b354(self->unk_3AA) == 2) {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                } else if ((func_020e92e8((void *) (&data_021cb5a0)) & 7) == 0) {
                    v[0] = ((int *) data_021fbee8)[0];
                    v[1] = ((int *) data_021fbee8)[1];
                    v[2] = ((int *) data_021fbee8)[2];
                    if (func_ov074_022795d8((struct UnkStruct_022795d8 *) self, v, &v[2]) != 0) {
                        dir = func_0200322c(self->unk_5C, v);
                        if (func_0201c3dc((short) (dir - self->unk_8E)) != 0) {
                            mode = 1;
                            if (func_020644cc(4) == 0) {
                                mode = 2;
                            }
                            if (mode != GetState(self)) {
                                func_02019d0c(sub, mode, 1, v[0], v[2], 0, 0, 0, 0, data_020c80f8, 0);
                                self->unk_651 = 0x64;
                            }
                        } else {
                            if (GetState(self) != 4) {
                                func_02019d0c(sub, 4, 1, v[0], v[2], 0, dir, 0, 0, data_020c80f8, 0);
                                self->unk_651 = 0x50;
                            }
                        }
                    } else {
                        func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                    }
                } else {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
            } else {
                if (self->unk_98 != 0) {
                    if (GetState(self) == 1 || GetState(self) == 2 || GetState(self) == 4) {
                        if (self->unk_651 == 0) {
                            func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                        } else {
                            p = func_0201afd0(self->unk_350);
                            v2[0] = p[0];
                            v2[1] = p[1];
                            v2[2] = p[2];
                            if (func_0201c3dc((short) (func_0200322c(self->unk_5C, v2) - self->unk_8E)) == 0) {
                                func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (self->unk_98 != 0) {
            func_ov074_02279778(self, 3);
        }
    }
    return 0;
}

int func_ov074_022791e0(char *self)
{
    func_02019d0c((void *) (self + 0x564), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    self[0x651] = 0;
    func_02013c04(self + 0x558);
    return 1;
}

int func_ov074_022791c4(int param)
{
    int result;
    int local = param;

    result = func_ov074_02279668((void *) param);
    if (result != 0) {
        func_ov074_02279778((UnkStruct_02279230 *) local, 2);
    }
    return 1;
}

int func_ov074_022791c0(void)
{
    return 1;
}

int func_ov074_02279194(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov074_02279778((UnkStruct_02279230 *) self, 1);
    }
    return 1;
}

int func_ov074_02279190(void)
{
    return 1;
}

int func_ov074_02279154(char *self)
{
    int size;
    int s;

    size = func_02016104(self + 0x658);
    s = *(short *) (self + 0x8e);

    if (size != 0) {
        s = func_0201c314(self, size);
    }

    func_020147fc(self + 0x618, 0, s, 0);
    return 1;
}

int func_ov074_02279150(void)
{
    return 1;
}
