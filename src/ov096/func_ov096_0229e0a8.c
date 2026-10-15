/* func_ov096_0229e0a8 @ 0x0229e0a8, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0204c878(unsigned short *);
extern int func_ov096_0229e158(void *receiver);
extern int func_0204c120(unsigned int, int, unsigned int *);
extern void func_ov096_0229e128(void *, unsigned int);

int func_ov096_0229e0a8(void *a0, unsigned short a1)
{
    unsigned short local = a1;
    unsigned int total;
    unsigned int amount;
    unsigned int diff;
    unsigned int extra;
    int result;

    amount = func_0204c878(&local);
    total = amount + func_ov096_0229e158(a0);
    result = 0xfff1;
    if (total > 99999) {
        diff = total - 99999;
        result = func_0204c120(diff, 1, &extra);
        total = total - (diff + extra);
    }
    func_ov096_0229e128(a0, total);
    return result;
}
