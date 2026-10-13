/* func_ov076_02278aac @ 0x02278aac, 0x44 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ea80(int, int);
extern int func_02014868(void *);

int func_ov076_02278aac(void *self)
{
    int result = 0;
    if (*(unsigned char *) ((char *) self + 0x71c) != 0) {
        return 0;
    }
    if (func_0202ea80(0x18, 0) == 1) {
        return 0;
    }
    if (func_02014868((char *) self + 0x618) == 0) {
        result = 1;
    }
    return result;
}
