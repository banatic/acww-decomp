/* func_ov052_02260880 @ 0x02260880, 0x34 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern int func_ov052_02260554(void *);

int func_ov052_02260880(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0 || func_0201c014(p) != 0 || func_ov052_02260554(p) != 0) {
        return 0;
    }
    return 1;
}
