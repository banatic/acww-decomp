/* func_ov133_0229b714 @ 0x0229b714, 0x28 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099658(int);
extern int func_0206fc8c(void);
extern void *func_02077d00(void *entries);

int func_ov133_0229b714(void *receiver)
{
    int base;
    int index;
    int result;

    base = func_02099658((int) func_020984e8());
    index = func_0206fc8c();
    result = (int) func_02077d00((void *) base);
    result += index * 0x24;
    return result;
}
