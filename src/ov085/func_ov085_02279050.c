/* func_ov085_02279050 @ 0x02279050, 0x2c bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern int func_0203e020(void *p);
extern void func_ov085_022790ec(void *p, int n);

int func_ov085_02279050(void *p)
{
    if (func_02014868((char *) p + 0x618) == 0) {
        func_0203e020(p);
        func_ov085_022790ec(p, 2);
    }
    return 1;
}
