/* func_ov047_02260610 @ 0x02260610, 0x2c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern int func_0201c014(void *p);

int func_ov047_02260610(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0 || func_0201c014(p) != 0) {
        return 0;
    }
    return 1;
}
