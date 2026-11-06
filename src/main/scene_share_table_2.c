/* scene_share_table_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020853b0 @ 0x020853b0, 0x6c bytes, Thumb
 * func_0208537c @ 0x0208537c, 0x34 bytes, Thumb
 * func_02085350 @ 0x02085350, 0x2a bytes, Thumb
 * func_02085310 @ 0x02085310, 0x40 bytes, Thumb
 * func_020852e4 @ 0x020852e4, 0x2c bytes, Thumb
 * func_02085278 @ 0x02085278, 0x6c bytes, Thumb
 * func_02085244 @ 0x02085244, 0x34 bytes, Thumb
 * func_0208520c @ 0x0208520c, 0x38 bytes, Thumb
 * func_020851e0 @ 0x020851e0, 0x2c bytes, Thumb
 * func_020851a0 @ 0x020851a0, 0x40 bytes, Thumb
 */

typedef struct UnkStruct_020853b0 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020853b0;

typedef struct {
    char flag;
    char pad_01[29];
} Entry;

typedef struct UnkStruct_02085278 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02085278;

struct Entry {
    unsigned char flag;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char pad_03[27];
};

struct UnkStruct_020851e0 {
    unsigned short unk_00;
};

extern unsigned char data_021d213c[];
extern void func_02077a54(void *, int, int);
extern void func_020779b8(void *, int, int);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void *func_0207b9d0(int index);
extern void func_020794c0(void *p, int x);
extern void func_020794a4(void *p, int x);
extern char data_021d2128;
extern int func_0207762c(int);
extern int func_020738bc(int a, int b);
extern int data_020ccf94;
extern unsigned char data_021d232c[];

void func_02085310(void *param0, int param1);

int func_020853b0(unsigned short *a0, int a1, UnkStruct_020853b0 *a2, int a3, const void *a4, const void *a5)
{
    unsigned char *e;
    unsigned int v;
    unsigned int off;
    v = *a0 & 0xfff;
    if (v >= 8) {
        goto fail;
    }
    off = v * 0x1e;
    e = &data_021d213c[off];
    data_021d213c[off] = 1;
    func_02077a54(e + 3, a1, 0);
    func_020779b8(e + 4, a2->unk_00, a2->unk_08);
    MI_CpuCopy8(&a3, e + 9, 2);
    MI_CpuCopy8(a4, e + 0xf, 0xf);
    MI_CpuCopy8(a5, e + 0xb, 4);
    return 1;
fail:
    return 0;
}

int func_0208537c(unsigned short *p, unsigned char a, unsigned char b)
{
    unsigned int val = *p & 0x0fff;
    if (val < 8) {
        unsigned char *ptr = data_021d213c + val * 30;
        ptr[0] = 1;
        ptr[1] = a;
        ptr[2] = b;
        return 1;
    }
    return 0;
}

void func_02085350(void *a, int index)
{
    void *r;

    func_02085310(a, index);
    r = func_0207b9d0(index - 12);
    if (r != 0) {
        func_020794c0(r, 0);
        func_020794a4(r, 0);
    }
}

void func_02085310(void *param0, int param1)
{
    int index = param1 - 12;
    if ((unsigned) index < 8) {
        int ret;
        ((Entry *) data_021d213c)[index].flag = 1;
        ret = func_0207762c(param1);
        MI_CpuCopy8((const void *) (&((Entry *) data_021d213c)[index]), param0, ret);
        data_021d2128 = 1;
    }
}

int func_020852e4(unsigned short *arg)
{
    unsigned int masked = ((unsigned int) *arg) & 0x0fff;
    int result;
    if (masked < 8) {
        result = func_020738bc(data_020ccf94, masked + 12);
    } else {
        result = 0;
    }
    return result;
}

int func_02085278(unsigned short *a0, int a1, UnkStruct_02085278 *a2, int a3, const void *a4, const void *a5)
{
    unsigned char *e;
    unsigned int v;
    unsigned int off;
    v = *a0 & 0xfff;
    if (v >= 0x26) {
        goto fail;
    }
    off = v * 0x1e;
    e = &data_021d232c[off];
    data_021d232c[off] = 1;
    func_02077a54(e + 3, a1, 0);
    func_020779b8(e + 4, a2->unk_00, a2->unk_08);
    MI_CpuCopy8(&a3, e + 9, 2);
    MI_CpuCopy8(a4, e + 0xf, 0xf);
    MI_CpuCopy8(a5, e + 0xb, 4);
    return 1;
fail:
    return 0;
}

int func_02085244(unsigned short *data, unsigned char a, unsigned char b)
{
    unsigned int index = *data & 0xFFF;
    if (index < 38) {
        struct Entry *e = &((struct Entry *) data_021d232c)[index];
        e->flag = 1;
        e->unk_01 = a;
        e->unk_02 = b;
        return 1;
    }
    return 0;
}

void func_0208520c(unsigned char *p0, int p1)
{
    unsigned int idx = p1 - 32;
    if (idx < 38) {
        unsigned int off = idx * 30;
        unsigned char *dst = (unsigned char *) ((char *) data_021d232c) + off;
        dst[0] = 1;
        MI_CpuCopy8((const void *) dst, (void *) p0, (unsigned int) func_0207762c(p1));
    }
}

int func_020851e0(struct UnkStruct_020851e0 *s)
{
    unsigned masked = (unsigned) (s->unk_00 & 0xfff);
    if (masked < 0x26) {
        return func_020738bc((int) ((*(void **) &data_020ccf94)), masked + 0x20);
    } else {
        return 0;
    }
}

int func_020851a0(unsigned short *p, int a, int b, int c, int d, int e)
{
    int nibble = (*p & 0xF000) >> 12;
    if (nibble == 14) {
        return func_020853b0(p, a, (UnkStruct_020853b0 *) b, c, (const void *) d, (const void *) e);
    }
    if (nibble == 13) {
        return func_02085278(p, a, (UnkStruct_02085278 *) b, c, (const void *) d, (const void *) e);
    }
    return 0;
}
