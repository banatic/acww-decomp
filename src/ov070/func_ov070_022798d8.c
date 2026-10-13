/* func_ov070_022798d8 @ 0x022798d8, 0x2c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(const void *p);
extern void func_0203e020(void *p);
extern void func_ov070_02279974(void *p, int n);

int func_ov070_022798d8(void *obj)
{
    if (func_02014868((char *) obj + 0x618) == 0) {
        func_0203e020(obj);
        func_ov070_02279974(obj, 2);
    }
    return 1;
}
