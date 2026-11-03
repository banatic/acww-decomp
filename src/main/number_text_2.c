/* number_text_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b47fc @ 0x020b47fc, 0x68 bytes, Thumb
 * func_020b47d0 @ 0x020b47d0, 0x2a bytes, Thumb
 * func_020b4758 @ 0x020b4758, 0x78 bytes, Thumb
 * func_020b46a4 @ 0x020b46a4, 0xb4 bytes, Thumb
 * func_020b45d0 @ 0x020b45d0, 0xd4 bytes, Thumb
 * func_020b4508 @ 0x020b4508, 0xc8 bytes, Thumb
 */

#include "types.h"

typedef struct Big {
    unsigned int w[0x18];
} Big;

typedef struct {
    char data[0x40];
} UnkStruct_020b4508;

typedef struct {
    char data[0x40];
} UnkStruct_020b4508_2;

typedef struct {
    char data[0x5c];
} UnkStruct_020b4508_3;

extern void func_020b4930(char *s, unsigned int len, int at, int n);
extern int func_020b4950_unk(const signed char *str);
extern const char data_020d20b8[];
extern const char data_020d2078[];
extern const char data_020d207c[];
extern const u8 data_020d20ac[];
extern const u8 data_020d2094[];
extern const u8 data_020d20a0[];
extern int data_020e5300;
extern void *func_020a8228(Big *s);
extern void *func_020a8210(Big *s);
extern int func_020b4a20(Big *s, u8 *v, void *p);
extern int func_020a89dc(void *ctx, Big *s);
extern void MI_CpuFill8(void *s, int c, unsigned int n);
extern void func_020b48ec(void *dst, unsigned int size, int a, int b);
extern void func_020b48b4(void *dst, unsigned int size, int a);
extern void func_020b488c(void *dst, unsigned int size, int a);
extern void func_020b4864(void *dst, unsigned int size, int a);
extern int func_020a8be4(int a0, void *ptr);
extern int FX_Modf(int, int *);
extern void *func_020b5630(void *);
extern int func_020a8bb8(void *, void *);
extern int func_020a89f8(void *, void *);
extern void *func_020b5618(void *);
extern int data_020d2080;

void func_020b47fc(char *s, unsigned int len, int group)
{
    int i;
    int cnt;
    char *q;
    int reset;
    int fill;

    i = 0;
    cnt = 0;
    fill = 0;
    reset = 0;
    while (s[i] != 0) {

        if (s[i] >= '0' && s[i] <= '9') {
            cnt++;
            if (cnt >= group) {
                unsigned int j;
                cnt = reset;
                j = i + 2;
                if (j < len) {
                    q = s + j;
                    if (s[j] >= '0' && s[j] <= '9') {
                        func_020b4930(s, len, i, 2);
                        *q = ',';
                        s[j + 1] = (char) fill;
                    }
                }
            }
        }
        i += 2;
    }
}

void func_020b47d0(signed char *str, unsigned int size)
{
    int len;
    unsigned int half;
    unsigned int i;
    int j;
    signed char tmp;

    len = func_020b4950_unk(str);
    half = (unsigned int) len >> 1;
    i = 0;
    j = len - 1;
    while (i < half) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

void func_020b4758(char *dst, unsigned int n, const char *src, unsigned int source_size)
{
    int i;
    const char *nul;
    int one;
    int zero;
    const char *e;
    const char *p;
    char *q;
    int ch;
    int c0;
    int c1;
    int sc;

    i = 0;
    nul = 0;
    one = 1;
    zero = 0;
    goto test;
body:
    c1 = p[one];
    ch = ((c1 << 8) & 0xff) | c0;
    e = nul;
    sc = (signed char) ch;
    if (sc >= '0' && sc <= '9') {
        e = &data_020d20b8[(sc - '0') * 2];
    } else if (ch == 0x20) {
        e = data_020d2078;
    } else if (ch == 0x2c) {
        e = data_020d207c;
    }
    q = dst + i;
    q[1] = e[zero];
    dst[i] = e[one];
    i += 2;
test:
    p = src + i;
    c0 = src[i];
    if (c0 != 0) {
        goto body;
    }
    if (p[one] != 0) {
        goto body;
    }
    dst[i] = 0;
    dst = dst + i;
    dst[1] = 0;
}

int func_020b46a4(void *ctx, int n, int kind)
{
    u8 v;
    Big s;
    int r;
    int m;

    func_020a8228(&s);
    r = 0;
    m = n % 10;
    if (kind == 1) {
        r = 0;
    } else if (kind == 2) {
        r = 1;
    } else if (kind == 3) {
        r = data_020d20ac[m];
    } else if (kind == 4) {
        r = 5;
    } else if (kind == 5) {
        r = 6;
    } else if (kind == 6) {
        r = data_020d2094[m];
    } else if (kind == 7) {
        r = 10;
    } else if (kind == 8) {
        r = 11;
    } else if (kind == 9) {
        r = data_020d20a0[m];
    } else if (kind == 10) {
        r = 14;
    }
    v = r;
    r = func_020b4a20(&s, &v, &data_020e5300);
    if (r != 0) {
        r = (r & func_020a89dc(ctx, &s)) != 0;
    }
    func_020a8210(&s);
    return r;
}

int func_020b45d0(int a0, int a1, int a2, int a3, int a4, unsigned char a5)
{
    unsigned char A[0x1c];
    unsigned char B[0x1e];
    void *p;
    int ret;

    MI_CpuFill8(A, 0, sizeof(A));
    func_020b48ec(A, sizeof(A), a1, a2);

    if (a3 == 2) {
        goto do_23;
    }
    if (a3 == 3) {
        goto do_23;
    }
    goto skip_23;
do_23:
    func_020b48b4(A, sizeof(A), a2);
skip_23:

    if (a3 == 4) {
        goto do_45;
    }
    if (a3 == 5) {
        goto do_45;
    }
    goto skip_45;
do_45:
    func_020b488c(A, sizeof(A), a2);
skip_45:

    if (a3 == 6) {
        goto do_67;
    }
    if (a3 == 7) {
        goto do_67;
    }
    goto skip_67;
do_67:
    func_020b4864(A, sizeof(A), a2);
skip_67:

{
    unsigned int ok = 0;
    unsigned int idx = (unsigned int) (a3 - 1);
    if (idx <= 6) {
        if ((1u << idx) & 0x55) {
            ok = 1;
        }
    }
    if (ok) {
        func_020b47fc((char *) A, sizeof(A), 3);
    }
}

    func_020b47d0((signed char *) A, sizeof(A));

    p = A;
    if (a5 == 0) {
        MI_CpuFill8(B, 0, sizeof(B));
        func_020b4758((char *) B, sizeof(B), (const char *) A, sizeof(A));
        p = B;
    }

    ret = func_020a8be4(a0, p);

    if (a4 != 0) {
        ret &= func_020b46a4((void *) a0, a1, a4);
        ret = ret ? 1 : 0;
    }

    return ret;
}

int func_020b4508(void *p, int q, int n)
{
    int local;
    UnkStruct_020b4508 A;
    UnkStruct_020b4508_2 B;
    UnkStruct_020b4508_3 C;
    int i;
    int acc;
    int shifted;
    int flag;
    int result;
    int ret;

    acc = FX_Modf(q, &local);

    for (i = 0; i < n; i++) {
        acc = acc * 10;
    }

    shifted = local >> 12;

    func_020b5630(&A);
    func_020b5630(&B);
    func_020a8228((Big *) (&C));

    ret = func_020b45d0((int) (&A), shifted, 10, 0, 0, 0);
    flag = (ret & 1) ? 1 : 0;

    ret = func_020b45d0((int) (&B), acc >> 12, 10, 0, 0, 0);
    result = (flag & ret) ? 1 : 0;

    ret = func_020a8bb8(p, &A);
    result = (result & ret) ? 1 : 0;

    ret = func_020a89f8(p, &data_020d2080);
    result = (result & ret) ? 1 : 0;

    ret = func_020a89dc(p, (Big *) (&B));
    result = (result & ret) ? 1 : 0;

    func_020a8210((Big *) (&C));
    func_020b5618(&B);
    func_020b5618(&A);

    return result;
}
