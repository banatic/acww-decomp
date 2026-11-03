/* board_notices: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02042a08 @ 0x02042a08, 0x52 bytes, Thumb
 * func_020429a0 @ 0x020429a0, 0x66 bytes, Thumb
 * func_02042954 @ 0x02042954, 0x4a bytes, Thumb
 * func_020428e8 @ 0x020428e8, 0x6c bytes, Thumb
 * func_0204287c @ 0x0204287c, 0x6c bytes, Thumb
 * func_02042798 @ 0x02042798, 0xe4 bytes, Thumb
 * func_02042730 @ 0x02042730, 0x68 bytes, Thumb
 * func_020426d8 @ 0x020426d8, 0x58 bytes, Thumb
 * func_02042684 @ 0x02042684, 0x54 bytes, Thumb
 * func_020425a8 @ 0x020425a8, 0xdc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02042954 {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_02042954;

typedef struct {
    unsigned int a;
    unsigned int b;
} UnkStruct_02042730;

typedef struct {
    unsigned int a;
    unsigned int b;
} UnkStruct_020426d8;

extern int func_02077f3c(int, char *, unsigned char, unsigned char, unsigned char);
extern void MI_CpuFill8(void *, int, unsigned int);
extern char data_020db87c;
extern int func_020644cc(int a);
extern unsigned char data_020db870;
extern void MI_CpuCopy8(void *src, void *dst, int n);
extern int func_02094fd4(void *);
extern int func_02094fbc(void *);
extern int func_0207cec0(const void *, int);
extern unsigned int func_0208150c(unsigned int object);
extern int func_02003648(unsigned char *item);
extern int func_0208249c(char *out, int value);
extern int func_0203d7c4(int, void *);
extern int func_0203fcb4(int, void *, int);
extern unsigned int data_020cb5c0[];
extern const unsigned char data_020db864[];
extern unsigned char data_021e5a2c[];
extern int func_0209e380(void *, void *);
extern void func_0204cc34(void *, void *);
extern int func_0203fea0(void *a, void *b);
extern int func_02098880(void *);
extern int func_0203fae4(void);
extern void func_0209e29c(void *, int);

int func_02042a08(int unused, volatile unsigned char *dst, const unsigned char *src, int count)
{
    int i;
    int zeros = 0;
    int cur = *src;

    for (i = 0; i < count; ++i) {
        *dst = (cur >> (i & 7)) & 1;
        if (*dst == 0) {
            ++zeros;
        }
        if ((i + 1) % 8 == 0) {
            ++src;
            cur = *src;
        }
        ++dst;
    }

    return zeros;
}

void func_020429a0(void *unused, unsigned char *dst, const unsigned char *src, int count)
{
    int i;
    i = 0;
    while (i < count) {
        unsigned int b7 = src[7] << 7;
        unsigned int b6 = src[6] << 6;
        unsigned int b5 = src[5] << 5;
        unsigned int b4 = src[4] << 4;
        unsigned int b3 = src[3] << 3;
        unsigned int b2 = src[2] << 2;
        unsigned int b0 = src[0];
        unsigned int b1 = src[1] << 1;
        *dst = (unsigned char) (b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7);
        src += 8;
        dst++;
        i++;
    }
}

int func_02042954(int unused, int limit, char *ptr, unsigned char *buf, int count, UnkStruct_02042954 *info)
{
    int i = 0;
    if (buf != 0) {
        int n = 0;
        while (n < count) {
            if (*buf == 0) {
                if (--limit < 0) {
                    break;
                }
            }
            buf++;
            i++;
            n++;
        }
        *buf = 1;
    }
    return func_02077f3c(i, ptr, info->unk_05, info->unk_04, info->unk_03);
}

void func_020428e8(void *p0, char *p1, void *p2)
{
    unsigned int result;
    char tmp[8];
    char buffer[0x54];

    result = (unsigned int) func_02042a08((int) p0, (volatile unsigned char *) buffer, (const unsigned char *) (p1 + 0x1726a), 0x54);
    if (result == 0) {
        result = 0x54;
        MI_CpuFill8(buffer, 0, result);
    }
    result = (unsigned int) func_020644cc(result);
    MI_CpuCopy8(p2, (void *) tmp, 8);
    func_02042954((int) p0, result, (char *) (&data_020db87c), (unsigned char *) buffer, 0x54, (UnkStruct_02042954 *) tmp);
    func_020429a0(p0, (unsigned char *) (p1 + 0x1726a), (const unsigned char *) buffer, 0xb);
}

void func_0204287c(char *a, char *b, char *c)
{
    unsigned char buf[0x4c];
    unsigned char arr[8];
    int ret;

    ret = func_02042a08((int) a, (volatile unsigned char *) buf, (const unsigned char *) (b + 0x17260), 0x4c);
    if (ret == 0) {
        ret = 0x4c;
        MI_CpuFill8(buf, 0, ret);
    }
    ret = func_020644cc(ret);
    MI_CpuCopy8(c, arr, 8);
    func_02042954((int) a, ret, (char *) (&data_020db870), (unsigned char *) buf, 0x4c, (UnkStruct_02042954 *) arr);
    func_020429a0(a, (unsigned char *) (b + 0x17260), (const unsigned char *) buf, 0xa);
}

void func_02042798(int unused, unsigned char *p, unsigned char *q)
{
    int i;
    int r5;
    int c;
    int v10;
    int v14;
    char buf18[8];
    char buf20[36];

    func_02094fd4(buf20);
    i = 0;
    v10 = 0;
    c = 0;
    r5 = -1;
    v14 = i;

    for (i = 0; i < 7; i++) {
        int code;
        unsigned int record;
        unsigned int item;
        r5 = -1;
        code = *(unsigned short *) p;
        switch (code) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                if ((record = func_0207cec0((const void *) data_021e5a2c, code)) != 0 && (item = func_0208150c(record)) != 0) {
                    func_0208249c(buf20, func_02003648((unsigned char *) item));
                    func_0203d7c4(c, buf20);
                    r5 = func_020644cc(3) + 0x1e;
                }
                break;
            default:
                if (code >= 0x1c && code < 0x3a) {
                    int ret;
                    MI_CpuCopy8((void *) q, buf18, 8);
                    ret = func_0203fcb4(code, buf18, v10);
                    switch (ret) {
                        case 2:
                        case 3:
                            r5 = data_020cb5c0[code - 0x1c];
                            break;
                        default:
                            break;
                    }
                }
                break;
        }
        if (r5 != ~v14) {
            func_02077f3c(r5, (char *) data_020db864, q[5], q[4], q[3]);
        }
        p += 12;
    }

    func_02094fbc(buf20);
}

int func_02042730(int unused, u8 *p1, u8 *p2)
{
    UnkStruct_02042730 local;
    int result = 0;
    int b = p1[2];

    if (b == 0xff && p1[1] == 0xff && p1[0] == 0xff) {
        result = 1;
    } else if (b == p2[5] && p1[1] == p2[4] && p1[0] == p2[3]) {
        ;
    } else {
        result = 0;
        local.a = result;
        local.b = result;
        local.a = result;
        local.b = result;
        ((u8 *) &local)[5] = p1[2];
        ((u8 *) &local)[4] = p1[1];
        ((u8 *) &local)[3] = p1[0];
        result = func_0209e380(&local, p2);
        if (result > 0x1f) {
            result = 0x1f;
        } else if (result < 0) {
            result = 1;
        }
    }
    return result;
}

void func_020426d8(int unused, unsigned char *base, int b)
{
    unsigned char *p;
    UnkStruct_020426d8 local;

    local.a = 0;
    local.b = 0;

    p = base + 0x1725c;

    local.a = 0;
    local.b = 0;

    ((unsigned char *) &local)[5] = p[2];
    ((unsigned char *) &local)[4] = p[1];
    ((unsigned char *) &local)[3] = p[0];

    while (func_0209e380((void *) b, &local) < 0) {
        func_0204cc34(base + 0x17254, p);
        ((unsigned char *) &local)[5] = p[2];
        ((unsigned char *) &local)[4] = p[1];
        ((unsigned char *) &local)[3] = p[0];
    }
}

void func_02042684(int a, char *b, void *src)
{
    struct UnkStruct_02042684 {
        int x;
        int y;
    } s0, s1, s2;
    char t4[84];

    s0.x = 0;
    s0.y = 0;

    MI_CpuCopy8(src, &s0, 8);
    MI_CpuCopy8(&s0, &s1, 8);
    if (func_0203fea0(t4, &s1) > 0) {
        MI_CpuCopy8(&s0, &s2, 8);
        func_02042798(a, (unsigned char *) t4, (unsigned char *) (&s2));
    }
    b[0x17276] = 1;
}

void func_020425a8(void *a0, u8 *o, int n, const void *src, int wd)
{
    int flag;
    u32 b[2];
    u32 a[2];
    u32 c[2];
    u32 d[2];
    u8 *p3;
    int w;

    flag = 0;
    b[0] = 0;
    b[1] = 0;
    a[0] = 0;
    a[1] = 0;
    p3 = o + 0x1725c;
    MI_CpuCopy8((void *) src, a, 8);
    w = wd;

    if (o[0x17276] != 0 || func_02098880(o + 0x14) > 1 || func_0203fae4() == 0) {
        flag = 1;
    }

    while (n > 0) {
        b[0] = 0;
        b[1] = 0;
        ((u8 *) b)[5] = p3[2];
        ((u8 *) b)[4] = p3[1];
        ((u8 *) b)[3] = p3[0];
        if (func_0209e380(a, b) == 0) {
            MI_CpuCopy8((void *) b, c, 8);
            func_0204287c((char *) a0, (char *) o, (char *) c);
            func_0204cc34(o + 0x17254, p3);
        }
        if (w == 1) {
            MI_CpuCopy8((void *) a, d, 8);
            func_020428e8(a0, (char *) o, d);
        }
        if (flag != 0) {
            func_02042684((int) a0, (char *) o, a);
        }
        n = n - 1;
        w = (w + 1) % 7;
        func_0209e29c(a, 1);
    }
}
