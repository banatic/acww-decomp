/* func_ov003_02217c5c @ 0x02217c5c, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020110c4(void *out, void *self);
extern int func_ov003_02217838(void *self, int a, int b, int c, int a5, short a6, int a7, short a8);
extern unsigned int func_0200e92c(void *w);
extern void func_0200e90c(void *w, int k, int a7, short a8);
extern void func_ov003_02217d1c(void *p, int a, int b, int c, int a5, short a6);
extern void func_0200f268(void *self, int f);
extern int func_0200e894(void *self, void *w);
extern int func_0200e91c(void *w);

typedef struct {
    volatile unsigned short a;
    unsigned short b;
} UnkStruct_02217c5c;
typedef struct {
    char pad_00[0xc];
    char inner[0x10];
} UnkStruct_02217c5c_2;

int func_ov003_02217c5c(void *self, int a, int b, int c, int a5, short a6, int a7, short a8)
{
    UnkStruct_02217c5c v;
    UnkStruct_02217c5c_2 w;
    unsigned int ok;
    unsigned short lo, hi;
    int r;

    func_020110c4(&v, self);
    ok = 0;
    lo = v.a;
    hi = v.a;
    if (hi >= 0x1380 && lo <= 0x139f) {
        ok = 1;
    }
    if (ok != 0 || (lo >= 0x13a0 && lo <= 0x13a7)) {
        return func_ov003_02217838(self, a, b, c, a5, a6, a7, a8);
    }
    func_0200e92c(&w);
    func_0200e90c(&w, 0x3d, a7, a8);
    func_ov003_02217d1c(w.inner, a, b, c, a5, a6);
    func_0200f268(self, 1);
    r = func_0200e894(self, &w);
    func_0200e91c(&w);
    return r;
}
