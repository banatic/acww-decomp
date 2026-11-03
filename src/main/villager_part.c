/* villager_part: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209ad9c @ 0x0209ad9c, 0x14 bytes, Thumb
 * func_0209ad2c @ 0x0209ad2c, 0x70 bytes, Thumb
 * func_0209ac50 @ 0x0209ac50, 0xdc bytes, Thumb
 * func_0209ac30 @ 0x0209ac30, 0x20 bytes, Thumb
 * func_0209ac04 @ 0x0209ac04, 0x2c bytes, Thumb
 * func_0209abd0 @ 0x0209abd0, 0x32 bytes, Thumb
 * func_0209abc8 @ 0x0209abc8, 0x8 bytes, Thumb
 * func_0209abc0 @ 0x0209abc0, 0x8 bytes, Thumb
 * func_0209abb0 @ 0x0209abb0, 0x10 bytes, Thumb
 * func_0209ab94 @ 0x0209ab94, 0x1a bytes, Thumb
 * func_0209ab78 @ 0x0209ab78, 0x1a bytes, Thumb
 * func_0209ab34 @ 0x0209ab34, 0x44 bytes, Thumb
 * func_0209aacc @ 0x0209aacc, 0x68 bytes, Thumb
 * func_0209aa9c @ 0x0209aa9c, 0x2e bytes, Thumb
 * func_0209aa80 @ 0x0209aa80, 0x1a bytes, Thumb
 * func_0209a9a8 @ 0x0209a9a8, 0xd8 bytes, Thumb
 * func_0209a934 @ 0x0209a934, 0x74 bytes, Thumb
 * func_0209a918 @ 0x0209a918, 0x1c bytes, Thumb
 * func_0209a8fc @ 0x0209a8fc, 0x1a bytes, Thumb
 * func_0209a8c4 @ 0x0209a8c4, 0x38 bytes, Thumb
 * func_0209a8a4 @ 0x0209a8a4, 0x1e bytes, Thumb
 * func_0209a854 @ 0x0209a854, 0x50 bytes, Thumb
 * func_0209a850 @ 0x0209a850, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x60];
    int unk_60;
    char pad_64[0x70 - 0x64];
    int unk_70;
} UnkStruct_0209aacc;

typedef struct {
    unsigned short unk_00;
    unsigned char m[12];
    unsigned char pad_0E;
    unsigned char unk_0F;
} Rec;

typedef struct {
    char pad_00[0x70];
    char data[1];
} UnkStruct_0209a918;

extern int func_0209bd44(void *p);
extern void *func_0209b4cc(const void *p, int data);
extern int memcmp(const void *a, const void *b, int n);
extern void *func_0209b0f0(void *);
extern int func_0209b0c4(void *, void *);
extern void *func_0209b4d4(void *);
extern void *func_0209bb70(void *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_02003618(void *, void *);
extern void func_02003738(void *ptr);
extern int func_0209bba8(int x);
extern void func_0209b56c(void *);
extern int func_0209b4d8(int a, int b, int c, int d);
extern int func_0207cb9c(int *a, int b, int c);
extern int func_0208150c(int a);
extern void func_02003728(char *a, int b);
extern int data_021e5a2c[];
extern char *func_02137550(void *, int);
extern int func_0209bc40(int a);
extern int func_0209bba0(int a);
extern int func_020984e8(void);
extern int func_02099640(int object);
extern int func_02065ec0(void *b);
extern int func_02065f64(void *b);
extern void *func_02003760(Rec *r, int v);
extern int func_02003750(Rec *r);
extern void func_0209bb90(void *c, int k);
extern int func_02003704(void *);

void func_0209abc0(int p0);

void *func_0209ad9c(void *base, int index)
{
    void *result = 0;
    if (index >= 0 && index < 2) {
        result = (char *) base + index * 48;
    }
    return result;
}

void *func_0209ad2c(char *base, char *key, int data)
{
    void *result;
    char *elem;
    void *tmp;
    int i;

    result = 0;
    if (func_02003704((void *) key)) {
        for (i = 0; i < 2; i++) {
            elem = base + i * 0x30;
            tmp = func_0209b4d4((void *) elem);
            if (!func_0209bd44(tmp)) {
                continue;
            }
            tmp = func_0209b4cc(elem, data);
            if (*(unsigned short *) tmp != *(unsigned short *) key) {
                continue;
            }
            if (memcmp((char *) tmp + 2, key + 2, 12) != 0) {
                continue;
            }
            if (*(unsigned char *) ((char *) tmp + 0xf) != *(unsigned char *) (key + 0xf)) {
                continue;
            }
            result = elem;
            break;
        }
    }
    return result;
}

int func_0209ac50(char *a0, void *a1, u16 *p)
{
    int result;
    unsigned int ok;
    unsigned int t;
    int mode;
    void *h;
    void *q;
    int eq;

    result = 0;
    ok = 0;
    if (*p >= 0x155f && *p <= 0x1560) {
        ok = 1;
    }
    if (ok != 0) {
        if (func_0209bd44(func_0209b0f0(a0 + 0x94)) != 0) {
            result = func_0209b0c4(a0 + 0x94, a1);
            goto end;
        }
    }
    mode = 0;
    t = 0;
    if (*p >= 0x1561 && *p <= 0x1564) {
        t = 1;
    }
    if (t != 0) {
        mode = 0;
    }
    h = func_0209ad9c(a0, mode);
    if (h != 0) {
        q = func_0209b4d4((void *) h);
        if (func_0209bd44(q) != 0) {
            q = func_0209bb70(q);
            if (func_0204bcdc(q) != 0) {
                eq = (func_0204bc64(q) == func_0204bc64(p)) ? 1 : 0;
            } else {
                eq = (*(u16 *) q == *p) ? 1 : 0;
            }
            if (eq != 0) {
                result = func_02003618(func_0209b4cc((const void *) h, 1), a1);
            }
        }
    }
end:
    return result;
}

void func_0209ac30(void *base)
{
    int i = 0;
    char *p = (char *) base + 0x60;
    for (; i < 3; i++) {
        func_02003738(p + i * 16);
    }
}

int func_0209ac04(int a)
{
    int t;
    t = (int) func_0209b4d4((void *) func_0209ad9c((void *) a, 0));
    if (func_0209bd44((void *) t) != 0) {
        if (func_0209bba8(t) == 1) {
            return 1;
        }
    }
    return 0;
}

void func_0209abd0(void *arg)
{
    void *ret_val;
    ret_val = func_0209ad9c(arg, 0);
    func_0209b56c(ret_val);
    func_0209b4d8((int) ret_val, 0xb, 0, 0);
    func_0209ac30(arg);
    func_0209abc0((int) arg);
}

void func_0209abc8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (144))) + (0)) = 1;
}

void func_0209abc0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (144))) + (0)) = 0;
}

int func_0209abb0(unsigned char *p)
{
    if (p[0x90] == 1) {
        return 1;
    }
    return 0;
}

void func_0209ab94(int a)
{
    int zero = 0;
    func_0209b4d8((int) func_0209ad9c((void *) a, 0), 0xC, zero, zero);
}

void func_0209ab78(int a)
{
    func_0209b4d8((int) func_0209ad9c((void *) a, 0), 13, 0, 0);
}

void func_0209ab34(char *A)
{
    int zero = 0;
    int t0, t1;
    t0 = (int) func_0209ad9c((void *) A, zero);
    t1 = func_0207cb9c(data_021e5a2c, zero, zero);
    func_0209b4d8(t0, 14, zero, func_0208150c(t1));
    func_02003728(A + 0x60, func_0208150c(t1));
}

void func_0209aacc(UnkStruct_0209aacc *p)
{
    void *local;
    int r5, r6;
    int x, y;

    r6 = (int) func_0209ad9c(p, 0);
    func_0209b4d4((void *) r6);
    func_02137550(&local, 4);

    r5 = 0;
    if (func_02003704((void *) (&p->unk_60)) != 0) {
        local = &p->unk_60;
        r5 = 1;
    }

    r5 = func_0207cb9c((int *) ((void *) ((unsigned char *) data_021e5a2c)), (int) (&local), r5);
    x = func_0208150c(r5);
    func_0209b4d8(r6, 0xf, 0, x);
    y = func_0208150c(r5);
    p = (UnkStruct_0209aacc *) ((char *) p + 0x70);
    func_02003728((char *) p, y);
}

void func_0209aa9c(int arg0)
{
    int val;
    val = ((int) func_0209b4d4((void *) (int) func_0209ad9c((void *) arg0, 0)));
    if (func_0209bc40(val) == 15) {
        if (func_0209bba0(val) == 0) {
            func_0209bb90((void *) val, 1);
        }
    }
}

void func_0209aa80(void)
{
    int forwarded_value;

    if ((forwarded_value = (int) func_020984e8()) != 0) {
        func_0209aa9c((int) func_02099640((int) forwarded_value));
    }
}

int func_0209a9a8(void *a, void *b)
{
    Rec tmp;
    void *h;
    void *c;
    int v;
    Rec *p;

    if (b == 0) {
        goto fail;
    }
    if (func_02065ec0(b) == 0) {
        goto fail;
    }
    h = func_0209ad9c(a, 0);
    c = func_0209b4d4((void *) h);
    if (func_0209bc40((int) c) != 0xf) {
        goto fail;
    }
    v = func_02065f64(b);
    if (v != 0) {
        func_02003760(&tmp, v);
        if (func_02003704((void *) (&tmp)) != 0) {
            p = (Rec *) func_0209b4cc((const void *) h, 1);
            if (p->unk_00 == tmp.unk_00 && memcmp(p->m, tmp.m, 0xc) == 0 && p->unk_0F == tmp.unk_0F) {
                if ((unsigned int) func_0209bba0((int) c) < 2) {
                    func_0209bb90(c, 2);
                    func_02003750(&tmp);
                    return 1;
                }
                goto cleanup;
            }
        }
        if ((unsigned int) func_0209bba0((int) c) != 0) {
            goto cleanup;
        }
        func_0209bb90(c, 1);
        func_02003750(&tmp);
        return 1;
    cleanup:
        func_02003750(&tmp);
        goto fail;
    } else {
        if ((unsigned int) func_0209bba0((int) c) == 0) {
            func_0209bb90(c, 1);
            return 1;
        }
    }
fail:
    return 0;
}

void func_0209a934(char *arg)
{
    unsigned int key;
    void *list[2];
    int count;
    int i;
    unsigned int res;
    void *elem;

    key = (unsigned int) func_0209ad9c(arg, 0);
    func_02137550(list, 8);
    count = 0;
    for (i = 0; i < 2; i++) {
        elem = arg + 0x60 + i * 0x10;
        if (func_02003704(elem)) {
            list[count] = elem;
            count++;
        }
    }
    res = (unsigned int) func_0207cb9c((int *) (((int *) data_021e5a2c)), (int) list, count);
    func_0209b4d8(key, 0x10, 0, (unsigned int) func_0208150c(res));
    func_02003728((char *) (arg + 0x80), (unsigned int) func_0208150c(res));
}

void func_0209a918(UnkStruct_0209a918 *p)
{
    int ret;
    ret = (int) func_0209ad9c((void *) p, 0);
    func_0209b4d8(ret, 17, 0, (int) p->data);
}

int func_0209a8fc(int arg)
{
    return func_0209b4d8((int) func_0209ad9c((void *) arg, 0), 0x12, 0, 0);
}

void func_0209a8c4(void *param)
{
    void *p;
    p = (func_0209b4d4((void *) (int) func_0209ad9c(param, 0)));
    if (func_0209bd44(p) != 0 && func_0209bc40((int) p) == 0x12 && func_0209bba0((int) p) == 0) {
        func_0209bb90(p, 1);
    }
}

void func_0209a8a4(int r0)
{
    int r4 = r0;
    if (func_0209ac04(r0) != 0) {
        func_0209b56c((void *) func_0209ad9c((void *) r4, 0));
    }
}

int func_0209a854(void *r0, void *r1)
{
    int r5 = (int) r0;
    int r4 = (int) r1;
    if (func_02003704((void *) r4) != 0) {
        if (func_0209ac04((int) ((void *) r5)) != 0) {
            if (*(unsigned short *) r4 == *(unsigned short *) (r5 + 0x70)) {
                if (memcmp((const void *) ((void *) (r4 + 2)), (const void *) ((void *) (r5 + 0x72)), 0xc) == 0) {
                    if (*(unsigned char *) (r4 + 0xf) == *(unsigned char *) (r5 + 0x7f)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int func_0209a850(int p0)
{
    return ((int) (p0) + (148));
}
