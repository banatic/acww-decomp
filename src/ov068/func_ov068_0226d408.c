/* func_ov068_0226d408 @ 0x0226d408, 0xa4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int argument0);
extern int func_02003704(void *argument0);
extern unsigned int func_0207f1c8(void *);
extern void *func_0209b5ec(void *argument0);
extern int func_0209c330(void *argument0);
extern int func_020644cc(int);
extern void func_0209e474(int *);
extern int func_0209c1cc(void *, int *, int);
extern int func_0209c38c(int);
extern int func_0201cddc(void *);
extern void *func_0207f270(void *);
extern void func_020794c8(void *, int);

struct Vtbl0 {
    char pad_00[0x64];
    void *(*func)(void *);
};
struct Self0 {
    struct Vtbl0 *vt;
};

void func_ov068_0226d408(struct Self0 *self)
{
    int v5; // first declared, goes to r5
    int v4; // second, goes to r4
    void *v6;
    int v7;
    int local[2];
    void *p1;
    int v;

    v6 = self->vt->func(self);
    if (v6 == 0) {
        return;
    }

    if (func_02003704((void *) func_0208150c((unsigned int) v6)) == 0) {
        return;
    }
    v5 = 8;

    p1 = func_0209b5ec((void *) func_0207f1c8(v6));
    v4 = func_0209c330(p1);
    v7 = func_020644cc(0x64);
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (v7 < 0x1e) {
        if (func_0209c1cc(p1, local, 3) != 0) {
            v4 = (unsigned char) func_020644cc(v5);
        }
    }
    if (func_0209c38c(v4) != 0 || v4 == 8) {
        v5 = v4;
    }
    v = func_0201cddc(self);
    switch (v) {
        case 3:
            v5 = 1;
            break;
        case 4:
            v5 = 0;
            break;
        case 5:
            v5 = 5;
            break;
        default:
            break;
    }
    func_020794c8(func_0207f270(v6), v5);
}
