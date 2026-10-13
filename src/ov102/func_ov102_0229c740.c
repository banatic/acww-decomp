/* func_ov102_0229c740 @ 0x0229c740, 0x50 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229c298(void *p, int v);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088ac(void *p);

void func_ov102_0229c740(void *r5, void *r4)
{
    if (func_ov002_022088cc(r4) != 0) {
        ((unsigned char *) r5)[0x25a5] = 0x21;
    }
    if (func_ov002_0220889c(r4) != 0) {
        ((unsigned char *) r5)[0x25a5] = 0;
        func_ov102_0229c298(r5, 0x20);
    } else if (func_ov002_022088ac(r4) != 0) {
        ((unsigned char *) r5)[0x25a5] = 4;
    }
}
