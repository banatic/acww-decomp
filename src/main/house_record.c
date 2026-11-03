/* house_record: 40 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02060f40 @ 0x02060f40, 0x1c bytes, Thumb
 * func_02060f30 @ 0x02060f30, 0x10 bytes, Thumb
 * func_02060f04 @ 0x02060f04, 0x2c bytes, Thumb
 * func_02060ee0 @ 0x02060ee0, 0x24 bytes, Thumb
 * func_02060eac @ 0x02060eac, 0x34 bytes, Thumb
 * func_02060e88 @ 0x02060e88, 0x24 bytes, Thumb
 * func_02060e78 @ 0x02060e78, 0x10 bytes, Thumb
 * func_02060e28 @ 0x02060e28, 0x50 bytes, Thumb
 * func_02060e10 @ 0x02060e10, 0x18 bytes, Thumb
 * func_02060de4 @ 0x02060de4, 0x2c bytes, Thumb
 * func_02060da8 @ 0x02060da8, 0x3c bytes, Thumb
 * func_02060d7c @ 0x02060d7c, 0x2c bytes, Thumb
 * func_02060d70 @ 0x02060d70, 0xc bytes, Thumb
 * func_02060d64 @ 0x02060d64, 0xc bytes, Thumb
 * func_02060d48 @ 0x02060d48, 0x1c bytes, Thumb
 * func_02060d3c @ 0x02060d3c, 0xc bytes, Thumb
 * func_02060d24 @ 0x02060d24, 0x18 bytes, Thumb
 * func_02060cf4 @ 0x02060cf4, 0x30 bytes, Thumb
 * func_02060cbc @ 0x02060cbc, 0x38 bytes, Thumb
 * func_02060c80 @ 0x02060c80, 0x3c bytes, Thumb
 * func_02060c60 @ 0x02060c60, 0x20 bytes, Thumb
 * func_02060bf8 @ 0x02060bf8, 0x68 bytes, Thumb
 * func_02060be0 @ 0x02060be0, 0x18 bytes, Thumb
 * func_02060b84 @ 0x02060b84, 0x5c bytes, Thumb
 * func_02060b70 @ 0x02060b70, 0x12 bytes, Thumb
 * func_02060b48 @ 0x02060b48, 0x28 bytes, Thumb
 * func_02060b34 @ 0x02060b34, 0x14 bytes, Thumb
 * func_02060b18 @ 0x02060b18, 0x1c bytes, Thumb
 * func_02060afc @ 0x02060afc, 0x1c bytes, Thumb
 * func_02060aac @ 0x02060aac, 0x50 bytes, Thumb
 * func_02060a98 @ 0x02060a98, 0x14 bytes, Thumb
 * func_02060a94 @ 0x02060a94, 0x2 bytes, Thumb
 * func_02060a90 @ 0x02060a90, 0x2 bytes, Thumb
 * func_02060a70 @ 0x02060a70, 0x1e bytes, Thumb
 * func_02060a34 @ 0x02060a34, 0x3c bytes, Thumb
 * func_02060a14 @ 0x02060a14, 0x20 bytes, Thumb
 * func_020609dc @ 0x020609dc, 0x38 bytes, Thumb
 * func_020609bc @ 0x020609bc, 0x20 bytes, Thumb
 * func_02060984 @ 0x02060984, 0x38 bytes, Thumb
 * func_02060974 @ 0x02060974, 0xe bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int unk_15A0;
} UnkStruct_02060e88;

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int field : 3;
} UnkStruct_02060e78;

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int lo : 3;
    unsigned int bits : 3;
    unsigned int hi : 26;
} UnkStruct_02060e28;

typedef struct {
    char pad_00[0x15a0];
    struct {
        unsigned int : 10;
        unsigned int nibble : 4;
        unsigned int : 18;
    } unk_15A0;
} UnkStruct_02060de4;

struct Func02060d3cData {
    unsigned char pad_00[0x1590];
    int unk_1590;
};

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int : 3;
    unsigned int value : 3;
} UnkStruct_02060cbc;

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int : 18;
    unsigned int field : 6;
    unsigned int : 8;
} UnkStruct_02060bf8;

typedef struct UnkStruct_02060aac UnkStruct_02060aac;

typedef struct UnkStruct_02060a34 UnkStruct_02060a34;

extern int func_020b67e8(int);
extern int func_020b6818(int);
extern int *func_0206122c(int, int);
extern unsigned short data_020cc9ec[][5];
extern unsigned char data_021ebcd4[];
extern unsigned short data_020cc9c0[];
extern int data_020cc9d0[];
extern int func_0209f150(void *, int);
extern unsigned char data_021dc7a8[];
extern void *func_02061188(unsigned int object);
extern void __register_global_object(void *, void *, void *);
extern void func_020051b0(void *);
extern unsigned short data_021cb4f4;
extern unsigned int data_021cb4fc;
extern unsigned char data_021cb564;
extern unsigned char func_020b65c4(void);
extern void func_0206117c(void *node, void *param);
extern unsigned char data_021ed268[];

int func_02060ee0(int a, int b);
unsigned int func_02060e78(UnkStruct_02060e78 *s);
unsigned short func_02060da8(int unused, int b);

void func_02060f40(unsigned char *r0)
{
    *(unsigned int *) (r0 + 0x1590) = 0x4d58;
    *(unsigned char *) (r0 + 0x15a3) = 0;
}

int func_02060f30(int x)
{
    if (x >= 0 && x < 5) {
        return 1;
    } else {
        return 0;
    }
}

int func_02060f04(int r0, int r1)
{
    int r4;
    int r5;
    int result;

    r5 = r0;
    r4 = r1;

    if (func_020b67e8(r4) != 0) {
        result = func_02060ee0(r5, func_020b6818(r4));
    } else {
        result = 0;
    }

    return result;
}

int func_02060ee0(int a, int b)
{
    int ret = 0;
    if (func_02060f30(b)) {
        ret = a + b * 0x450;
    }
    return ret;
}

int *func_02060eac(int arg0, int arg1, int arg2)
{
    int *p = 0;
    int ret = func_02060ee0(arg0, arg1);
    if (ret) {
        p = func_0206122c(ret, arg2);
        if (p) {
            *p = (int) func_02060da8(arg0, arg1);
        }
    }
    return p;
}

int func_02060e88(UnkStruct_02060e88 *obj)
{
    int ret;
    ret = (int) func_02060e78((UnkStruct_02060e78 *) obj);
    if (((obj->unk_15A0 << 26) >> 29) == ret) {
        return 0;
    } else {
        return 1;
    }
}

unsigned int func_02060e78(UnkStruct_02060e78 *s)
{
    return s->field;
}

int func_02060e28(UnkStruct_02060e28 *p)
{
    if (p->bits == (unsigned int) (int) func_02060e78((UnkStruct_02060e78 *) p)) {
        if ((int) func_02060e78((UnkStruct_02060e78 *) p) < 6) {
            p->bits = (unsigned char) ((int) func_02060e78((UnkStruct_02060e78 *) p) + 1);
            return 1;
        }
    }
    return 0;
}

unsigned int func_02060e10(unsigned int *arg0)
{
    unsigned int r0;
    unsigned int r1;

    r1 = 0x15a0;
    r0 = arg0[r1 >> 2];
    r0 = r0 << 0x16;
    r1 = r0 >> 0x1c;
    r1 = r1 & 0xf;
    r0 = r1 << 0x18;
    r0 = r0 >> 0x18;
    return r0;
}

int func_02060de4(UnkStruct_02060de4 *s, unsigned char val)
{
    s->unk_15A0.nibble = (unsigned char) (val & 0xF);
    return 1;
}

unsigned short func_02060da8(int unused, int b)
{
    int x;
    if (b == -1) {
        goto L1;
    }
    x = (int) func_02060e78((UnkStruct_02060e78 *) ((void *) data_021ebcd4));
    if (x >= 7) {
        goto L2;
    }
    return data_020cc9ec[x][b];
L2:
    return 0x1002;
L1:
    return 0x1002;
}

unsigned short func_02060d7c(void *addr)
{
    int res;
    res = (int) func_02060e78((UnkStruct_02060e78 *) (((char *) data_021ebcd4)));
    if (res < 7) {
        return data_020cc9c0[res];
    } else {
        return 0x1003;
    }
}

unsigned char func_02060d70(void *arg0)
{
    return ((unsigned char *) arg0)[0x15a3];
}

void func_02060d64(unsigned char *base, unsigned char value)
{
    base[0x15a3] = value;
}

void func_02060d48(unsigned char *data, int param)
{
    if (param >= 7) {
        int temp = data[0x15a3] + (param - 6);
        if (temp > 10) {
            temp = 10;
        }
        data[0x15a3] = (unsigned char) temp;
    }
}

int func_02060d3c(struct Func02060d3cData *arg)
{
    return arg->unk_1590;
}

// placeholder, not used
void func_02060d24(int *r0, int r1)
{
    if (r1 < 0) {
        *(int *) ((char *) r0 + 0x1590) = 0;
    } else {
        *(int *) ((char *) r0 + 0x1590) = r1;
    }
}

void func_02060cf4(int arg)
{
    unsigned int index;

    if (func_02060d3c((struct Func02060d3cData *) arg) != 0) {
        return;
    }
    index = func_02060e78((UnkStruct_02060e78 *) arg);
    if (index >= 7) {
        return;
    }
    func_02060d24((int *) arg, data_020cc9d0[index]);
}

int func_02060cbc(UnkStruct_02060cbc *arg)
{
    int ret;
    ret = (int) func_02060e78((UnkStruct_02060e78 *) arg);
    if (arg->value != ret) {
        goto ret_zero;
    }
    if (func_02060d3c((struct Func02060d3cData *) arg) != 0) {
        goto ret_zero;
    }
    return func_0209f150((void *) data_021dc7a8, 13);
ret_zero:
    return 0;
}

int func_02060c80(int param1, int param2)
{
    int result;
    int temp;
    int mask;
    int shifted;
    int value;
    int *ptr;

    result = func_02060e28((UnkStruct_02060e28 *) ((void *) param1));
    if (result != 0) {
        ptr = (int *) (param1 + 0x15a0);
        value = *ptr;
        mask = 0xfffc3fff;
        value &= mask;
        shifted = param2 & 0xf;
        shifted <<= 0xe;
        value |= shifted;
        *ptr = value;
        return 1;
    }
    return 0;
}

unsigned char func_02060c60(unsigned int code)
{
    int ret;
    unsigned char result;

    ret = func_020b6818(code);
    result = 0;
    if (ret != -1) {
        result = (unsigned char) (1 << ret);
    }
    return result;
}

int func_02060bf8(UnkStruct_02060bf8 *self, int input, int flag)
{
    int result = (int) func_02060c60(input);
    if (result != 0) {
        if (flag) {
            self->field |= result;
        } else {
            self->field &= ~result;
        }
        return 1;
    } else {
        return 0;
    }
}

int func_02060be0(unsigned int *r0)
{
    unsigned int r1;
    unsigned int r0_val;
    int result;

    r1 = 0x15a0;
    r0_val = r0[r1 / 4];
    r0_val = (r0_val << 8) >> 0x1a;
    if (r0_val == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void *func_02060b84(int param)
{
    int forwarded_value;

    if ((forwarded_value = (int) func_02060f04((int) (((unsigned char *) data_021ebcd4)), param)) != 0) {
        return func_02061188((unsigned int) forwarded_value);
    }
    if (!(data_021cb4fc & 1)) {
        data_021cb4f4 = 0xfff1;
        __register_global_object((void *) (&data_021cb4f4), (((void *) func_020051b0)), (void *) (&data_021cb564));
        data_021cb4fc |= 1;
    }
    return &data_021cb4f4;
}

void *func_02060b70(void)
{
    return func_02060b84((int) func_020b65c4());
}

int func_02060b48(void *key, void *param)
{
    void *res;
    res = (void *) func_02060f04((int) (((char *) data_021ebcd4)), (int) key);
    if (res != 0) {
        func_0206117c(res, param);
        return 1;
    }
    return 0;
}

void *func_02060b34(void *p)
{
    return (void *) func_02060b48((void *) func_020b65c4(), p);
}

int func_02060b18(int a)
{
    unsigned short val = 0xfff1;
    return func_02060b48((void *) a, (void *) (&val));
}

void func_02060afc(void)
{
    unsigned short local;
    unsigned short *p;

    p = &local;
    *p = 0x0000fff1;
    func_02060b34((void *) p);
}

int func_02060aac(void *a, unsigned short *b)
{
    unsigned int i;
    UnkStruct_02060aac *g = ((UnkStruct_02060aac *) data_021ebcd4);
    void *e = (void *) func_02060f04((int) g, (int) a);
    if (e != 0) {
        for (i = 0; i < 5; i++) {
            void *x = (void *) func_02060ee0((int) g, i);
            if (e != x) {
                unsigned short v = *(unsigned short *) func_02061188((unsigned int) x);
                if (v == *b) {
                    return 1;
                }
            }
        }
        return 0;
    }
    return 0;
}

int func_02060a98(int arg)
{
    return func_02060aac((void *) ((int) func_020b65c4()), (unsigned short *) arg);
}

void func_02060a94(void *receiver) {}

void func_02060a90(int value) {}

int func_02060a70(unsigned char *arr, unsigned int idx)
{
    if (idx < 70) {
        if ((arr[idx >> 3] >> (idx & 7)) & 1) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}

static __inline int idxOf(unsigned int x)
{
    if (x >= 0x1323 && x <= 0x1368) {
        return (int) (x - 0x1323);
    }
    return -1;
}

int func_02060a34(unsigned int x)
{
    if (x >= 0x1323 && x <= 0x1368) {
        return func_02060a70((unsigned char *) (((UnkStruct_02060a34 *) data_021ed268)), idxOf(x));
    }
    return 0;
}

void func_02060a14(unsigned char *array, unsigned int bit)
{
    if (bit < 70) {
        array[bit >> 3] |= 1 << (bit & 7);
    }
}

void func_020609dc(unsigned int param0)
{
    if (param0 >= 0x1323 && param0 <= 0x1368) {
        int delta;
        if (param0 >= 0x1323 && param0 <= 0x1368) {
            delta = param0 - 0x1323;
        } else {
            delta = -1;
        }
        func_02060a14((unsigned char *) ((unsigned int) data_021ed268), delta);
    }
}

void func_020609bc(unsigned char *bitmap, unsigned int bit_index)
{
    if (bit_index < 0x46) {
        unsigned int byte_index = bit_index >> 3;
        unsigned char value = bitmap[byte_index];
        value &= ~(1 << (bit_index & 7));
        bitmap[byte_index] = value;
    }
}

void func_02060984(unsigned int param)
{
    int value;
    if (param < 0x1323) {
        return;
    }
    if (param > 0x1368) {
        return;
    }
    if (param >= 0x1323 && param <= 0x1368) {
        value = (int) (param - 0x1323);
    } else {
        value = -1;
    }
    func_020609bc(data_021ed268, value);
}

void func_02060974(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 9; i++) {
        p[i] = 0;
    }
}
