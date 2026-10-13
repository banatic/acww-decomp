/* func_ov105_0229dd30 @ 0x0229dd30, 0x38 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b19c(void *);
extern void func_ov105_0229c330(void *, int);
extern void func_ov105_0229db14(void *);

void func_ov105_0229dd30(char *p)
{
    if (func_ov094_0229b19c(p + 0xd5c)) {
        func_ov105_0229c330(p, 0x1000);
        p[0x2b4] = 0;
        func_ov105_0229db14(p);
    }
}
