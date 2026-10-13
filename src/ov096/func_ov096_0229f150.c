/* func_ov096_0229f150 @ 0x0229f150, 0x58 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *a, void *b);
extern int func_ov096_0229f820(void *a, void *b);
extern void *func_ov096_0229f7ac(void *a, void *b);
extern void *func_ov096_0229f548(void *a, void *b);
extern int func_ov094_0229a69c(void *a, void *b);
extern int func_ov094_0229b30c(void *a, void *b);

int func_ov096_0229f150(void *self, void *arg)
{
    if (func_ov096_0229f830(self, arg)) {
        return func_ov094_0229a69c((char *) self + 0x358, func_ov096_0229f7ac(self, arg));
    }
    if (func_ov096_0229f820(self, arg)) {
        return func_ov094_0229b30c((char *) self + 0xdb8, func_ov096_0229f548(self, arg));
    }
    return 1;
}
