/* func_ov052_02260854 @ 0x02260854, 0x2c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0201c014(void *);

int func_ov052_02260854(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
