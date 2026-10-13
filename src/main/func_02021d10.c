/* func_02021d10 @ 0x02021d10, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d60(int);
extern int func_02081398(int, int);
extern unsigned short *func_02095040(int);
extern int memcmp(const void *, const void *, unsigned int);

int func_02021d10(int a, int b)
{
    unsigned short *p = (unsigned short *) (a + 0x7dc);
    int flag = 0;
    if (func_02081398(a, func_02081d60(b)) != 0) {
        unsigned short *q = func_02095040(func_02081d60(b));
        if (*q == *p) {
            if (memcmp(q + 1, p + 1, 12) == 0) {
                flag = 1;
            }
        }
    }
    return flag;
}
