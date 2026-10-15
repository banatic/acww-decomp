/* func_ov096_0229e0f8 @ 0x0229e0f8, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c878(unsigned short *);
extern int func_ov096_0229e158(void *receiver);
extern void func_ov096_0229e128(void *, int);

void func_ov096_0229e0f8(void *a, unsigned short b)
{
    unsigned short value = b;
    int amount = func_0204c878(&value);
    func_ov096_0229e158(a);
    func_ov096_0229e128(a, func_ov096_0229e158(a) - amount);
}
