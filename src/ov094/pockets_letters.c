/* pockets_letters: 17 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229b384 @ 0x0229b384, 0x6c bytes, Thumb
 * func_ov094_0229b328 @ 0x0229b328, 0x5c bytes, Thumb
 * func_ov094_0229b30c @ 0x0229b30c, 0x1a bytes, Thumb
 * func_ov094_0229b2b0 @ 0x0229b2b0, 0x5c bytes, Thumb
 * func_ov094_0229b29c @ 0x0229b29c, 0x12 bytes, Thumb
 * func_ov094_0229b288 @ 0x0229b288, 0x12 bytes, Thumb
 * func_ov094_0229b274 @ 0x0229b274, 0x12 bytes, Thumb
 * func_ov094_0229b220 @ 0x0229b220, 0x54 bytes, Thumb
 * func_ov094_0229b1e8 @ 0x0229b1e8, 0x38 bytes, Thumb
 * func_ov094_0229b1d8 @ 0x0229b1d8, 0x10 bytes, Thumb
 * func_ov094_0229b1d0 @ 0x0229b1d0, 0x8 bytes, Thumb
 * func_ov094_0229b19c @ 0x0229b19c, 0x34 bytes, Thumb
 * func_ov094_0229b184 @ 0x0229b184, 0x18 bytes, Thumb
 * func_ov094_0229b174 @ 0x0229b174, 0x10 bytes, Thumb
 * func_ov094_0229b154 @ 0x0229b154, 0x1e bytes, Thumb
 * func_ov094_0229b134 @ 0x0229b134, 0x1e bytes, Thumb
 * func_ov094_0229b110 @ 0x0229b110, 0x24 bytes, Thumb
 */

typedef struct {
    unsigned int pad_00;
    unsigned char *unk_04;
    unsigned int pad_08;
} UnkStruct_0229b220;

typedef struct {
    char pad_00[0x26];
    unsigned char counter;
    unsigned char result;
} UnkStruct_0229b19c;

extern unsigned char data_ov094_0229c0ec[];
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098e44(int, int);
extern int func_02065ec0(int a);
extern int func_02065f18(int a);
extern unsigned char data_ov094_0229bddc[];

void func_ov094_0229b220(UnkStruct_0229b220 *self, unsigned char *val, int idx, int count);
int func_ov094_0229b1e8(int a, int b);
int func_ov094_0229b184(unsigned char *p);
void func_ov094_0229b154(int *arr, int bit);
void func_ov094_0229b134(unsigned int *arr, int bit);
int func_ov094_0229b110(int *bits, int n);

int func_ov094_0229b384(int arg0, int param)
{
    if (param >= 0 && param <= 9) {
        if (param & 1) {
            return 0xe4;
        } else {
            return 0xcc;
        }
    } else if (param >= 10 && param <= 34) {
        param -= 10;
        while (param >= 5) {
            param -= 5;
        }
        return data_ov094_0229c0ec[param];
    } else if (param >= 35 && param <= 44) {
        if ((param - 35) & 1) {
            return 0x84;
        } else {
            return 0x6c;
        }
    } else if (param >= 45 && param <= 54) {
        if ((param - 45) & 1) {
            return 0x84;
        } else {
            return 0x6c;
        }
    } else {
        return 0;
    }
}

int func_ov094_0229b328(int arg0, int key)
{
    if (key >= 0 && key <= 9) {
        return 0x3c + 24 * (key >> 1);
    }
    if (key >= 10 && key <= 34) {
        int count;
        key -= 10;
        count = 0;
        while (key >= 5) {
            key -= 5;
            count++;
        }
        return 0x3c + 24 * count;
    }
    if (key >= 35 && key <= 44) {
        return 0x3c + 24 * ((key - 35) >> 1);
    }
    if (key >= 45 && key <= 54) {
        return 0x3c + 24 * ((key - 45) >> 1);
    }
    return 0;
}

int func_ov094_0229b30c(int *p, int arg1)
{
    int result;
    if (func_ov094_0229b110(p + 2, arg1) != 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void func_ov094_0229b2b0(void *self)
{
    int v = func_02098e44(func_02099734(func_020984e8()), 0);
    int idx = 0;
    int i = 0;
    int zero = 0;
    do {
        if (func_ov094_0229b1e8((int) self, v) != ~zero) {
            func_ov094_0229b154((int *) ((char *) self + 8), idx);
        } else {
            func_ov094_0229b134((unsigned int *) ((char *) self + 8), idx);
        }
        v += 0x100;
        idx++;
        i++;
    } while (i < 10);
}

void func_ov094_0229b29c(int a, int b)
{
    func_ov094_0229b220((UnkStruct_0229b220 *) a, (unsigned char *) b, 45, 10);
}

void func_ov094_0229b288(int a, int b)
{
    func_ov094_0229b220((UnkStruct_0229b220 *) a, (unsigned char *) b, 10, 25);
}

void func_ov094_0229b274(int a, int b)
{
    func_ov094_0229b220((UnkStruct_0229b220 *) a, (unsigned char *) b, 0x23, 0xa);
}

void func_ov094_0229b220(UnkStruct_0229b220 *self, unsigned char *val, int idx, int count)
{
    int cond = 0;
    int i;
    unsigned char *p;

    self->unk_04 = val;
    p = self->unk_04;
    for (i = 0; i < count; i++) {
        if (func_ov094_0229b1e8((int) self, (int) p) != ~cond) {
            func_ov094_0229b154((int *) ((void *) ((char *) self + 8)), idx);
        } else {
            func_ov094_0229b134((unsigned int *) ((void *) ((char *) self + 8)), idx);
        }
        p += 0x100;
        idx++;
    }
}

int func_ov094_0229b1e8(int a, int b)
{
    int x;
    int r;
    x = func_02065ec0(b);
    if (x == 0) {
        return -1;
    }
    r = (x - 1) * 2;
    if (func_02065f18(b) != 0xfff1) {
        r++;
    }
    return r;
}

void func_ov094_0229b1d8(unsigned char *param0)
{
    param0[0x26] = 4;
    param0[0x27] = 10;
}

void func_ov094_0229b1d0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (39))) + (0)) = 10;
}

int func_ov094_0229b19c(UnkStruct_0229b19c *p)
{
    if (p->counter != 0) {
        p->counter--;
        p->result = (unsigned char) func_ov094_0229b184((unsigned char *) p);
        return 0;
    } else {
        func_ov094_0229b1d0((int) p);
        return 1;
    }
}

int func_ov094_0229b184(unsigned char *p)
{
    unsigned char idx = p[0x26];
    if (idx >= 4) {
        return 10;
    }
    return data_ov094_0229bddc[idx];
}

void func_ov094_0229b174(int *p)
{
    int i = 0;
    int v = i;
    do {
        p[i] = v;
        i++;
    } while (i < 2);
}

void func_ov094_0229b154(int *arr, int bit)
{
    arr[bit >> 5] |= 1 << (bit & 31);
}

void func_ov094_0229b134(unsigned int *arr, int bit)
{
    int idx;
    unsigned int mask;
    unsigned int val;

    idx = bit >> 5;
    mask = 1 << (bit & 0x1f);
    val = arr[idx];
    val &= ~mask;
    arr[idx] = val;
}

int func_ov094_0229b110(int *bits, int n)
{
    int result = 1;
    int mask = result << (n & 31);
    if (!(mask & bits[n >> 5])) {
        result = 0;
    }
    return result;
}
