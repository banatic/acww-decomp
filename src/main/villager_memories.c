/* villager_memories: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02080568 @ 0x02080568, 0x10 bytes, Thumb
 * func_0208053c @ 0x0208053c, 0x2c bytes, Thumb
 * func_0208052c @ 0x0208052c, 0x10 bytes, Thumb
 * func_02080500 @ 0x02080500, 0x2a bytes, Thumb
 * func_020804e8 @ 0x020804e8, 0x16 bytes, Thumb
 * func_020804b8 @ 0x020804b8, 0x2e bytes, Thumb
 * func_02080404 @ 0x02080404, 0xb4 bytes, Thumb
 * func_020803e0 @ 0x020803e0, 0x24 bytes, Thumb
 * func_02080330 @ 0x02080330, 0xae bytes, Thumb
 * func_020802ec @ 0x020802ec, 0x42 bytes, Thumb
 * func_020802c8 @ 0x020802c8, 0x22 bytes, Thumb
 * func_020802a4 @ 0x020802a4, 0x22 bytes, Thumb
 * func_020801c4 @ 0x020801c4, 0xe0 bytes, Thumb
 * func_02080190 @ 0x02080190, 0x34 bytes, Thumb
 * func_0208016c @ 0x0208016c, 0x22 bytes, Thumb
 * func_0208012c @ 0x0208012c, 0x3e bytes, Thumb
 * func_02080108 @ 0x02080108, 0x22 bytes, Thumb
 */

#include "types.h"

#define Compare_02080578 ((int (*)(void *, void *, void *)) func_02080578)

typedef struct {
    u32 data[8];
} V32;

typedef struct {
    u32 data[9];
} V36;

extern int func_02080578(unsigned short *, unsigned short *, void *);
extern int func_020805bc(void *, int (*)(void *, void *, void *));
extern const void *func_02095040(void *);
extern int memcmp(const void *, const void *, unsigned int);
extern int func_02080758(int param);
extern int func_020807c0(int a, int b);
extern int func_02081e94(int a, int b, int c, int d);
extern unsigned short data_021dc7aa[];
extern int func_020951bc(void *);
extern int func_02081edc(void *);
extern int func_02081d28(void *, void *);
extern unsigned short *func_02081d64(void *);
extern int func_0208150c(void *);
extern int func_02003704(int);
extern int func_02080cf0(void *);
extern int func_020806f8(void *);
extern int func_02080684(void *, void *);
extern int func_020807a8(int, int);
extern int func_02081d20(int);
extern void *func_02095074(int, int);
extern void func_02081c94(int, int);
extern int func_02081c40(int a1, int a2);
extern void func_02081c14(int, int, int);
extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern void *func_02094fd4(void *);
extern void *func_02094fbc(void *);
extern int func_020a89ac(void *, void *);
extern void func_020a8c1c(void *);
extern int func_02081c00(int);
extern int func_02081bc4(int, int);
extern void func_02081b68(void *object, void *source, int count);
extern int func_02081b54(void *r);
extern void func_02081b24(void *r, unsigned b);
extern void func_02081ac8(void *object, void *source, int count);

int func_02080568(int arg)
{
    return func_020805bc((void *) arg, Compare_02080578);
}

int func_0208053c(void *a, void *b, void *context)
{
    const void *p = func_02095040((void *) a);
    (void) context;

    if (*(const unsigned short *) b != *(const unsigned short *) p ||
        memcmp((const char *) b + 2, (const char *) p + 2, 12) != 0) {
        return 1;
    }
    return 0;
}

int func_0208052c(int p0)
{
    return func_020805bc((void *) p0, func_0208053c);
}

int func_02080500(int param)
{
    int result;
    int temp;

    result = func_02080758(param);
    if (result == -1) {
        result = func_02080568(param);
    }
    if (result == -1) {
        result = func_0208052c(param);
    }
    return result;
}

int func_020804e8(int a)
{
    int b;
    int c;

    b = a;
    c = func_02080500(a);
    return func_020807c0(b, c);
}

int func_020804b8(int a, int b)
{
    int ret;
    ret = func_020807a8(a, (int) ((void *) b));
    if (ret != 0) {
        goto done;
    }
    ret = func_020804e8(a);
    if (ret == 0) {
        goto done;
    }
    func_02081e94(ret, b, 0, 0);
done:
    return ret;
}

int func_02080404(void *self, void **out, void *arg2, int arg3)
{
    int count = 0;
    int i;
    if (data_021dc7aa != (unsigned short *) 0 && func_020951bc(arg2)) {
        for (i = 0; i < 8; i++) {
            void *slot = (char *) self + i * 0x80;
            if (func_02081edc(slot) != 0 && func_02081d28(slot, arg2) == 0) {
                switch (arg3) {
                    case 0: {
                        unsigned short *r = func_02081d64(slot);
                        if (r[0] == data_021dc7aa[0] && memcmp(r + 1, (const void *) ((char *) data_021dc7aa + 2), 0xc) == 0) {
                            out[count] = slot;
                            count++;
                        }
                        break;
                    }
                    case 1: {
                        unsigned short *r = func_02081d64(slot);
                        if (r[0] != data_021dc7aa[0] || memcmp(r + 1, (const void *) ((char *) data_021dc7aa + 2), 0xc) != 0) {
                            out[count] = slot;
                            count++;
                        }
                        break;
                    }
                    default:
                        out[count] = slot;
                        count++;
                        break;
                }
            }
        }
    }
    return count;
}

int func_020803e0(void *ptr)
{
    int count = 0;
    int i;
    for (i = count; i < 8; i++) {
        if (func_02081edc(ptr) != 0) {
            count++;
        }
        ptr = (char *) ptr + 0x80;
    }
    return count;
}

int func_02080330(void *a, void *b, void *c)
{
    int ea, eb;
    int va, vb;
    int fa, fb;

    if (func_02003704(func_0208150c(a)) == 0) {
        return 0;
    }
    if (func_02003704(func_0208150c(b)) == 0) {
        return 1;
    }

    ea = func_020803e0(a);
    eb = func_020803e0(b);
    if (ea > eb) {
        return 1;
    }
    if (ea < eb) {
        return 0;
    }

    va = func_02080cf0(a);
    vb = func_02080cf0(b);
    if (va != 0) {
        if (vb == 0) {
            return 1;
        }
    } else {
        if (vb != 0) {
            return 0;
        }
    }

    fa = func_020806f8(a);
    fb = func_020806f8(b);
    if (fa > fb) {
        return 1;
    }
    if (fa < fb) {
        return 0;
    }

    if (func_02080684(a, c) < func_02080684(b, c)) {
        return 1;
    }
    return 0;
}

void func_020802ec(int a0, int a1, int a2)
{
    int v = func_020807a8(a0, a2);
    if (!(v != 0 && func_020951bc((void *) a2) != 0 && func_02081d20(v) > -10)) {
        func_02095074(a2, a1);
    } else {
        func_02081c94(v, a1);
    }
}

int func_020802c8(int a1, int a2, int a3)
{
    int v1;
    int v2;

    v2 = func_020807a8(a1, a3);
    v1 = v2;
    if (v2 != 0) {
        func_02081c40(v2, a2);
    }
    return v1;
}

int func_020802a4(int a, int b, int c, int d)
{
    int ret = func_020807a8(a, d);
    if (ret != 0) {
        func_02081c14(ret, b, c);
    }
    return ret;
}

void func_020801c4(void *a, void *b, void *c)
{
    void *obj;
    V32 v1;
    V36 v2;
    void *p0, *p1;
    void *r6v, *r7v;

    if (c == 0) {
        c = func_020984e8();
    }
    if (c == 0) {
        return;
    }

    obj = func_02099870(c);
    if (func_020951bc(obj) == 0) {
        return;
    }
    if (func_02003704((int) ((void *) func_0208150c(a))) == 0) {
        return;
    }
    if (func_02003704((int) ((void *) func_0208150c(b))) == 0) {
        return;
    }

    r6v = 0;
    r7v = 0;
    p0 = (void *) func_020807a8((int) b, (int) obj);
    p1 = (void *) func_020807a8((int) a, (int) obj);

    func_02094fd4(&v1);
    func_02094fd4(&v2);

    if (p0 == 0 || p1 == 0) {
        goto done;
    }

    func_02095074((int) obj, (int) (&v2));
    func_02081c94((int) p0, (int) (&v1));
    if (func_020a89ac(&v2, &v1) == 0) {
        r7v = p0;
        r6v = p1;
    } else {
        func_020a8c1c(&v1);
        func_02081c94((int) p1, (int) (&v1));
        if (func_020a89ac(&v2, &v1) == 0) {
            r7v = p1;
            r6v = p0;
        }
    }

    if (r7v != 0 && r6v != 0) {
        func_020a8c1c(&v1);
        func_02081c94((int) r7v, (int) (&v1));
        func_02081c40((int) r6v, (int) (&v1));
    }

done:
    func_02094fbc(&v2);
    func_02094fbc(&v1);
}

int func_02080190(int a1, int a2, int a3)
{
    int p = func_020807a8(a1, a3);
    int result = p;
    if (result != 0) {
        result = func_020951bc((void *) a3);
        if (result != 0) {
            result = func_02081c00(p);
            if (result != 0) {
                result = func_02081bc4(p, a2);
            }
        }
    }
    return result;
}

void func_0208016c(int a1, int a2, int a3, int a4)
{
    int r = func_020807a8(a1, a4);
    if (r) {
        func_02081b68((void *) r, (void *) a2, a3);
    }
}

int func_0208012c(unsigned a, unsigned b, unsigned c)
{
    void *r;
    int flag;
    r = (void *) func_020807a8(a, c);
    flag = 0;
    if (r != 0 && func_020951bc((void *) c) != 0 && func_02081b54(r) != 0) {
        func_02081b24(r, b);
        flag = 1;
    }
    return flag;
}

void func_02080108(int p1, int p2, int p3, int p4)
{
    int ret = func_020807a8(p1, p4);
    if (ret != 0) {
        func_02081ac8((void *) ret, (void *) p2, p3);
    }
}
