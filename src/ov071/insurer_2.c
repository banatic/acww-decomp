/* insurer_2: 9 functions, module ov071
 * mwccarm 1.2/base -O4,s
 * func_ov071_02279760 @ 0x02279760, 0x78 bytes, Thumb
 * func_ov071_022796d0 @ 0x022796d0, 0x90 bytes, Thumb
 * func_ov071_02279694 @ 0x02279694, 0x3a bytes, Thumb
 * func_ov071_02279594 @ 0x02279594, 0x100 bytes, Thumb
 * func_ov071_02279570 @ 0x02279570, 0x22 bytes, Thumb
 * func_ov071_022792e0 @ 0x022792e0, 0x290 bytes, Thumb
 * func_ov071_02279290 @ 0x02279290, 0x50 bytes, Thumb
 * func_ov071_02279210 @ 0x02279210, 0x80 bytes, Thumb
 * func_ov071_0227920c @ 0x0227920c, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_02279760 {
    char pad_00[0x3b0];
    char unk_3B0;
    char pad_3B1[0x1a7];
    char unk_558;
    char pad_559[0xb];
    char unk_564;
    char pad_565[0x1c4];
    int unk_72C;
} UnkStruct_02279760;

struct UnkStruct_022796d0 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

typedef struct {
    char pad_00[0x5c];
    char sub;
    char pad_5D[0x37];
    short unk_94;
} UnkStruct_02279694;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_02279694_2;

typedef struct UnkStruct_022792e0 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x564 - 0x3aa];
    char unk_564[0x72c - 0x564];
    int unk_72C;
    char unk_730[4];
} UnkStruct_022792e0;

typedef struct {
    unsigned char pad_00[0x72c];
    int unk_72C;
} UnkStruct_02279290;

typedef struct {
    char pad_00[0x734];
    int unk_734;
} UnkStruct_02279210;

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern char data_021fbee8[];
int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
void func_02013c0c(void *a);
void func_0201ad18(void *a, int b, int c, int d, int e, int f, int g, int h);
extern int func_020e92e8(void *);
extern int FX_MulFunc(int, int);
extern void func_0204f7e0(int *, int *);
extern int func_02078e98(int *, int);
extern short FX_SinCosTable_[];
extern int data_021cb5a0;
extern void func_0201af58(void *buffer, const void *src, int c, int val);
extern int func_0201ae8c(const void *buffer);
extern void *func_0201ae40(void *p);
extern int func_0201aff8(void *p, void *self, int flag);
extern int func_0201afc0(void *p);
extern void func_0201af48(void *p);
extern void func_0201afd4(void *p, void *buf);
extern char data_ov071_0227a398;
extern char data_ov071_0227a38c;
extern int func_ov071_02279c08(UnkStruct_022792e0 *self, void *p);
extern int func_0202ea80(int a, int b);
extern int func_ov071_02279c18(UnkStruct_022792e0 *self, int a);
extern int func_ov071_02279b2c(UnkStruct_022792e0 *self, int a);
extern void func_ov071_02279d04(UnkStruct_022792e0 *self, int a);
extern int func_02019de8(void *p);
extern int func_0201b354(void *p);
extern int func_0200322c(void *p, int *v);
extern int func_0201c3dc(int a);
extern int func_020644cc(int a);
extern int func_02019e00(void *p);
extern int *func_0201afd0(void *p);
extern void func_02013c04(void *p);
extern int func_02096190(int);

int func_ov071_02279760(UnkStruct_02279760 *self)
{
    self->unk_72C = 0;
    func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_02013c0c(&self->unk_558);
    func_0201ad18(&self->unk_3B0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}

int func_ov071_022796d0(struct UnkStruct_022796d0 *self, int *out1, int *out2)
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

int func_ov071_02279694(UnkStruct_02279694 *a, UnkStruct_02279694_2 *b, int c)
{
    int ret = 0;
    int local[4];

    func_0201af58(local, &a->sub, c, a->unk_94);
    if (func_0201ae8c(local) != 1) {
        b->x = local[0];
        b->y = local[1];
        b->z = local[2];
        ret = 1;
    }
    return ret;
}

int func_ov071_02279594(void *self)
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
        if (func_ov071_02279694((UnkStruct_02279694 *) self, (UnkStruct_02279694_2 *) buf, (int) (&data_ov071_0227a398))) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    case2:
        if (func_ov071_02279694((UnkStruct_02279694 *) self, (UnkStruct_02279694_2 *) buf, (int) (&data_ov071_0227a38c))) {
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

int func_ov071_02279570(void *r0)
{
    if (*(int *) ((char *) r0 + 0x98) != 0) {
        if (func_ov071_02279594(r0)) {
            return 1;
        }
    }
    return 0;
}

static __inline int GetState(UnkStruct_022792e0 *self)
{
    return func_02019e00(self->unk_564);
}

int func_ov071_022792e0(UnkStruct_022792e0 *self)
{
    void *sub;
    int dir;
    int mode;
    int *p;
    int v[3];
    int v2[3];

    sub = self->unk_564;
    if (func_ov071_02279c08(self, self->unk_730) == 0 && func_0202ea80(0x28, 0) == 0 && func_ov071_02279c18(self, 0) != 0 &&
        func_ov071_02279b2c(self, 0x8000) != 0) {
        func_ov071_02279d04(self, 1);
        return 1;
    }
    func_ov071_02279c08(self, &self->unk_72C);
    if (func_ov071_02279c18(self, 1) != 0) {
        if (func_ov071_02279570((void *) self) == 0) {
            if (func_02019de8(sub) != 0) {
                if (func_0201b354(self->unk_3AA) == 2) {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                } else if ((func_020e92e8((void *) (&data_021cb5a0)) & 7) == 0) {
                    v[0] = ((int *) data_021fbee8)[0];
                    v[1] = ((int *) data_021fbee8)[1];
                    v[2] = ((int *) data_021fbee8)[2];
                    if (func_ov071_022796d0((struct UnkStruct_022796d0 *) self, v, &v[2]) != 0) {
                        dir = func_0200322c(self->unk_5C, v);
                        if (func_0201c3dc((short) (dir - self->unk_8E)) != 0) {
                            mode = 1;
                            if (func_020644cc(4) == 0) {
                                mode = 2;
                            }
                            if (mode != GetState(self)) {
                                func_02019d0c(sub, mode, 1, v[0], v[2], 0, 0, 0, 0, data_020c80f8, 0);
                                self->unk_72C = 0x64;
                            }
                        } else {
                            if (GetState(self) != 4) {
                                func_02019d0c(sub, 4, 1, v[0], v[2], 0, dir, 0, 0, data_020c80f8, 0);
                                self->unk_72C = 0x50;
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
                        if (self->unk_72C == 0) {
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
            func_ov071_02279d04(self, 4);
        }
    }
    return 0;
}

int func_ov071_02279290(UnkStruct_02279290 *self)
{
    func_02013c04((char *) self + 0x558);
    func_02019d0c((char *) self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    self->unk_72C = 0x28;
    return 1;
}

int func_ov071_02279210(UnkStruct_02279210 *p)
{
    p->unk_734 = func_02096190(4);

    if (func_0202ea80(0x28, 0) != 0) {
        if (func_ov071_02279c18((UnkStruct_022792e0 *) p, 1) != 0) {
            func_ov071_02279d04((UnkStruct_022792e0 *) p, 3);
            return 1;
        }
    } else {
        if (func_ov071_02279c18((UnkStruct_022792e0 *) p, 0) != 0 && func_ov071_02279b2c((UnkStruct_022792e0 *) p, 0x3000) == 0 && func_ov071_02279b2c((UnkStruct_022792e0 *) p, 0x8000) != 0) {
            func_ov071_02279d04((UnkStruct_022792e0 *) p, 1);
            return 1;
        }
        func_ov071_02279d04((UnkStruct_022792e0 *) p, 3);
    }
    return 1;
}

int func_ov071_0227920c(void)
{
    return 1;
}
