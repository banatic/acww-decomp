/* func_ov053_02260558 @ 0x02260558, 0xc8 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Tri;

extern int func_0203dff0(void *);
extern int func_ov053_02260474(void *);
extern void *func_020984e8(void);
extern Tri *func_02095794(int);
extern void func_0204f818(volatile int *, volatile int *, Tri *);
extern int func_020960f8(int, int);
extern int func_0203e070(void *, int);
extern int func_ov053_02260488(void *);
extern void func_ov053_02260bb0(void *, int);

int func_ov053_02260558(void *obj)
{
    volatile int a;
    volatile int b;
    Tri t;
    Tri *p;
    int hit;
    int v0, v1;

    if (func_0203dff0(obj) != 0) {
        return 0;
    }
    if (func_ov053_02260474(obj) == 0) {
        return 0;
    }
    func_020984e8();
    p = func_02095794(4);
    t.a = p->a;
    t.b = p->b;
    t.c = p->c;
    a = 0;
    b = 0;
    func_0204f818(&a, &b, &t);
    if (func_020960f8(0x25, 4) != 0 || func_020960f8(0x28, 4) != 0) {
        if (func_0203e070(obj, 0) != 0) {
            hit = 0;
            v0 = a;
            v1 = a;
            if (v1 == 4 && b == 0xb) {
                hit = 1;
            }
            if (hit != 0 || (v0 == 5 && b == 0xb)) {
                if (func_ov053_02260488(obj) != 0) {
                    func_ov053_02260bb0((char *) obj + 0x658, 3);
                } else {
                    func_ov053_02260bb0((char *) obj + 0x658, 4);
                }
            } else {
                func_ov053_02260bb0((char *) obj + 0x658, 7);
            }
            return 1;
        }
    }
    return 0;
}
