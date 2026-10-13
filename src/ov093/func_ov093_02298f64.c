/* func_ov093_02298f64 @ 0x02298f64, 0x20 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *p);
extern void func_020a8c1c(void *p);
extern int data_ov093_022998b8;

void *func_ov093_02298f64(void **p)
{
    func_020a8cac(p);
    *p = &data_ov093_022998b8;
    func_020a8c1c(p);
    return p;
}
