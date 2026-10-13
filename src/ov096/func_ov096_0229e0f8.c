/* func_ov096_0229e0f8 @ 0x0229e0f8, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c878(unsigned short *);
extern int func_ov096_0229e158(void *);
extern int func_ov096_0229e128(void *, int);

int func_ov096_0229e0f8(void *a, unsigned short b)
{
    unsigned short local;
    int v1;

    local = b;
    v1 = func_0204c878(&local);
    func_ov096_0229e158(a);
    return func_ov096_0229e128(a, func_ov096_0229e158(a) - v1);
}
