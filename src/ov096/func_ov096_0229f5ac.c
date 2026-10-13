/* func_ov096_0229f5ac @ 0x0229f5ac, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *a, void *b);
extern int func_ov096_0229f820(void *a, void *b);
extern void func_ov096_0229f5e0(void *a, void *b, int c, int d);

void func_ov096_0229f5ac(void *r5, void *r4)
{
    if (func_ov096_0229f830(r5, r4) == 0) {
        if (func_ov096_0229f820(r5, r4) == 0) {
            return;
        }
    }
    func_ov096_0229f5e0(r5, r4, 0x0000fff1, 0);
}
