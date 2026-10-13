/* func_020801c4 @ 0x020801c4, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 data[8];
} V32;

typedef struct {
    u32 data[9];
} V36;

extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern int func_020951bc(void);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern void *func_020807a8(void *, void *);
extern void func_02094fd4(void *);
extern void func_02094fbc(void *);
extern void func_02095074(void *, void *);
extern void func_02081c94(void *, void *);
extern void func_02081c40(void *, void *);
extern int func_020a89ac(void *, void *);
extern void func_020a8c1c(void *);

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
    if (func_020951bc() == 0) {
        return;
    }
    if (func_02003704(func_0208150c(a)) == 0) {
        return;
    }
    if (func_02003704(func_0208150c(b)) == 0) {
        return;
    }

    r6v = 0;
    r7v = 0;
    p0 = func_020807a8(b, obj);
    p1 = func_020807a8(a, obj);

    func_02094fd4(&v1);
    func_02094fd4(&v2);

    if (p0 == 0 || p1 == 0) {
        goto done;
    }

    func_02095074(obj, &v2);
    func_02081c94(p0, &v1);
    if (func_020a89ac(&v2, &v1) == 0) {
        r7v = p0;
        r6v = p1;
    } else {
        func_020a8c1c(&v1);
        func_02081c94(p1, &v1);
        if (func_020a89ac(&v2, &v1) == 0) {
            r7v = p1;
            r6v = p0;
        }
    }

    if (r7v != 0 && r6v != 0) {
        func_020a8c1c(&v1);
        func_02081c94(r7v, &v1);
        func_02081c40(r6v, &v1);
    }

done:
    func_02094fbc(&v2);
    func_02094fbc(&v1);
}
