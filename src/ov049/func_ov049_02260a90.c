/* func_ov049_02260a90 @ 0x02260a90, 0x34 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern int func_ov049_02260500(void *);

int func_ov049_02260a90(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0 || func_0201c014(p) != 0 || func_ov049_02260500(p) != 0) {
        return 0;
    }
    return 1;
}
