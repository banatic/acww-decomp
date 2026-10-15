/* func_ov096_0229f0dc @ 0x0229f0dc, 0x74 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *a, int b);
extern int func_ov096_0229f7ac(void *a, int b);
extern int func_ov096_0229f820(void *a, int b);
extern int func_ov096_0229f150(void *a, int b);
extern int func_ov096_0229f054(void *a, int b);
extern int func_ov096_0229f800(void *a, int b);
extern unsigned short func_02065f18(int x);
extern unsigned short func_ov094_0229aaac(void *addr, int x);

unsigned short func_ov096_0229f0dc(void *a, int b)
{
    if (func_ov096_0229f830(a, b)) {
        return func_ov094_0229aaac((char *) a + 0x358, func_ov096_0229f7ac(a, b));
    } else if (func_ov096_0229f820(a, b)) {
        if (func_ov096_0229f150(a, b)) {
            return 0xFFF1;
        } else {
            return func_02065f18(func_ov096_0229f054(a, b));
        }
    } else if (func_ov096_0229f800(a, b)) {
        return *(unsigned short *) ((char *) a + 0xae);
    }
    return 0xFFF1;
}
