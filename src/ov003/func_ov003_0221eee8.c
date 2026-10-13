/* func_ov003_0221eee8 @ 0x0221eee8, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int);
extern void func_ov003_0221eec4(void *);

void func_ov003_0221eee8(void)
{
    void *p;
    p = func_020edf70(0x2b4);
    if (p) {
        func_ov003_0221eec4(p);
    }
}
