/* func_ov106_0229c524 @ 0x0229c524, 0x28 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088cc(int);
extern void func_ov002_0220a2b4(void *);

void func_ov106_0229c524(char *p, int param1)
{
    if (func_ov002_022088cc(param1)) {
        func_ov002_0220a2b4(p + 0x22a0);
        p += 0xb8;
        *p = 0x13;
    }
}
