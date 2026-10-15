/* func_ov128_0229be5c @ 0x0229be5c, 0x1c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b168(void *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

void func_ov128_0229be5c(void *param)
{
    if (func_ov002_0220b168((char *) param + 0x94) == 0) {
        func_ov002_022080a0((void *) (param), 1);
    }
}
