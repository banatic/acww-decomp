/* func_020bd3b4 @ 0x020bd3b4, 0x2d4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Fn)(int);

typedef struct {
    unsigned char pad_00[0x2f18];
    unsigned char unk_2F18; // 0x2f18
    unsigned char unk_2F19; // 0x2f19
    unsigned char pad_2F1A[2];
    int unk_2F1C; // 0x2f1c
    unsigned char pad_2F20[0xc];
    int unk_2F2C; // 0x2f2c
    int unk_2F30; // 0x2f30
} SELF;

extern int func_02041614(int);
extern int func_0209e474(int *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0203fc78(int, void *, int);
extern int func_020b6640(void);
extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern int func_020644cc(int);
extern void func_020bc9c4(SELF *, int);
extern void *data_020ccf94;
typedef struct {
    int a;
    int b;
} UnkStruct_020bd3b4;
extern int data_021f6ccc;
extern UnkStruct_020bd3b4 data_021f6ed0[];
extern UnkStruct_020bd3b4 data_021f6f50[];
extern UnkStruct_020bd3b4 data_0213dd98;
extern UnkStruct_020bd3b4 data_020e5a20;
extern UnkStruct_020bd3b4 data_020e5ad0;
extern UnkStruct_020bd3b4 data_020e59d0;
extern UnkStruct_020bd3b4 data_020e5c20;
extern UnkStruct_020bd3b4 data_020e59e8;
extern UnkStruct_020bd3b4 data_020e5cf0;
extern UnkStruct_020bd3b4 data_020e59f0;
extern UnkStruct_020bd3b4 data_020e59e0;
extern UnkStruct_020bd3b4 data_020e5b18;
extern UnkStruct_020bd3b4 data_020e5b20;
extern UnkStruct_020bd3b4 data_020e5d80;
extern UnkStruct_020bd3b4 data_020e5b10;
extern UnkStruct_020bd3b4 data_020e5b08;
extern UnkStruct_020bd3b4 data_020e5a08;
extern UnkStruct_020bd3b4 data_020e5cd0;
extern UnkStruct_020bd3b4 data_020e5b40;
extern UnkStruct_020bd3b4 data_020e5a88;
extern UnkStruct_020bd3b4 data_020e5a10;
extern UnkStruct_020bd3b4 data_020e5a40;

void func_020bd3b4(SELF *self)
{
    int buf0[2];
    UnkStruct_020bd3b4 pe;
    UnkStruct_020bd3b4 *p;
    int b10[2];
    int b18[2];
    int b20[2];
    int b28[2];
    int r6, t7, res, res2, code, idx;
    unsigned int r4;
    UnkStruct_020bd3b4 *d;
    UnkStruct_020bd3b4 *e;
    int *th;
    Fn fn;

    r4 = 0;
    r6 = 0;
    buf0[0] = 0;
    buf0[1] = 0;
    t7 = func_02041614((int) self);
    func_0209e474(buf0);
    MI_CpuCopy8(buf0, b10, 8);
    res = func_0203fc78(0x13, b10, 1);
    if (res != 0) {
        unsigned char b1;
        unsigned char b2;
        int w;
        b1 = self->unk_2F19;
        b2 = self->unk_2F18;
        w = self->unk_2F1C;
        if (b1 >= 2) {
            goto endcheck;
        }
        r4 = 1;
        if (b1 != 0) {
            goto endcheck;
        }
        if (b2 != 0) {
            goto endcheck;
        }
        if (w != 0) {
            goto endcheck;
        }
        r6 = 1;
        goto endcheck;
    }
    if (t7 != 0xf) {
        goto L45c;
    }
    if (func_020b6640() == 0) {
        goto L430;
    }
    MI_CpuCopy8(buf0, b18, 8);
    res2 = func_0203fc78(0xf, b18, r4);
    if (res2 == 0) {
        goto endcheck;
    }
    r4 = 1;
    goto endcheck;
L430:
    if (func_02073d90(data_020ccf94) == 0) {
        goto L458;
    }
    MI_CpuCopy8(buf0, b20, 8);
    res2 = func_0203fc78(0xf, b20, r4);
    if (res2 == 0) {
        goto endcheck;
    }
    r4 = 1;
    goto endcheck;
L458:
    r4 = 1;
    goto endcheck;
L45c:
    if (func_020b65c4() != 0x2c) {
        goto endcheck;
    }
    MI_CpuCopy8(buf0, b28, 8);
    res2 = func_0203fc78(0xf, b28, 1);
    {
        int t = (res2 == 2) ? 1 : r4;
        if (t == 0) {
            goto endcheck;
        }
    }
    r4 = 1;

endcheck:
    if (r4 == 0) {
        goto failpath;
    }
    if ((data_021f6ccc & 1) == 0) {
        d = data_021f6ed0;
        d[0] = data_0213dd98;
        d[1] = data_020e5a20;
        d[2] = data_020e5ad0;
        d[3] = data_020e59d0;
        d[4] = data_020e5c20;
        d[5] = data_020e59e8;
        d[6] = data_020e5cf0;
        d[7] = data_020e59f0;
        d[8] = data_020e59e0;
        d[9] = data_020e5b18;
        d[10] = data_020e5b20;
        d[11] = data_020e5d80;
        d[12] = data_020e5b10;
        d[13] = data_020e5b08;
        d[14] = data_020e5a08;
        d[15] = data_020e5cd0;
        e = data_021f6f50;
        e[0] = data_020e5b40;
        e[1] = data_020e5a88;
        e[2] = data_020e5a10;
        e[3] = data_020e5a40;
        data_021f6ccc |= 1;
    }
    if (self->unk_2F2C == 0) {
        if (r6 != 0) {
            code = 0x12;
        } else {
            code = (func_020644cc(2) == 0) ? 0xe : 0x10;
        }
        func_020bc9c4(self, code);
        self->unk_2F30 = 0;
    }
    self->unk_2F30 -= 1;
    idx = self->unk_2F2C;
    pe = data_021f6ed0[idx];
    p = &pe;
    th = (int *) ((char *) self + (p->b >> 1));
    if (p->b & 1) {
        fn = *(Fn *) (*(int *) th + p->a);
    } else {
        fn = (Fn) p->a;
    }
    fn((int) th);
    return;
failpath:
    self->unk_2F2C = 0;
    self->unk_2F30 = 0;
    *(int *) ((char *) self + 0x2f34) = 0;
    *(int *) ((char *) self + 0x2f38) = 0;
    *(int *) ((char *) self + 0x2f3c) = 0;
    *(int *) ((char *) self + 0x2f40) = 0;
    *(int *) ((char *) self + 0x2f44) = 0;
    *(int *) ((char *) self + 0x2f48) = 0;
}
