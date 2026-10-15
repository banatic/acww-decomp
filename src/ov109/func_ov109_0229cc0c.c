/* func_ov109_0229cc0c @ 0x0229cc0c, 0x3e bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(char *a, void *b);
extern int func_ov109_0229cc98(char *a, void *b);
extern void func_ov094_0229aa14(char *a, int val, void *c, void *d);
extern void func_ov094_0229a9b4(char *a, int val);

void func_ov109_0229cc0c(char *a, void *b, void *c, void *d)
{
    if (func_ov109_0229ccb4(a, b)) {
        int val;
        val = func_ov109_0229cc98(a, b);
        func_ov094_0229aa14(a + 0xcc, val, c, d);
        a += 0xcc;
        func_ov094_0229a9b4(a, val);
    }
}
