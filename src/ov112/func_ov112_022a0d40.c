/* func_ov112_022a0d40 @ 0x022a0d40, 0x2c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char);
extern void func_ov112_022a19ec(void *);

void func_ov112_022a0d40(void *obj)
{
    if (func_ov002_02209f64((char *) obj + 0x4448) == 0) {
        func_ov002_02208098(obj, *(unsigned char *) ((char *) obj + 0xC1));
        func_ov112_022a19ec(obj);
    }
}
