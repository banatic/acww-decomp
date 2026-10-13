/* func_ov048_022604c8 @ 0x022604c8, 0xa4 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Tri;

extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern int func_0203ec98(int);
extern int func_02073dd4(void *, int);
extern Tri *func_02095794(int);
extern void *func_020984e8(void);
extern void func_ov048_02262678(void *, int);
extern void func_0203e0a8(void *, int);
extern void *data_020ccf94;
extern const Tri data_ov048_02263968;

int func_ov048_022604c8(void *obj)
{
    void *g;
    int v;
    volatile Tri t;
    Tri *p;

    g = data_020ccf94;
    if (func_02073d90(g) != 0) {
        return 0;
    }
    v = func_020b65c4();
    if (v == 0x2f) {
        return 0;
    }
    if (func_0203ec98(v) != 0) {
        return 0;
    }
    if (func_02073dd4(data_020ccf94, *(int *) ((char *) data_020ccf94 + 0x64)) == 0) {
        return 0;
    }
    p = func_02095794(4);
    t.a = p->a;
    t.b = p->b;
    t.c = p->c;
    if (p->c <= data_ov048_02263968.c) {
        func_020984e8();
        if (func_02073d90(g) != 0) {
            func_ov048_02262678((char *) obj + 0x658, 9);
        } else {
            func_ov048_02262678((char *) obj + 0x658, 0xa);
        }
        func_0203e0a8(obj, 0);
        return 1;
    }
    return 0;
}
