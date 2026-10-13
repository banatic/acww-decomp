/* func_ov093_02298f4c @ 0x02298f4c, 0x18 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *, void *);
extern char data_ov093_022998b8;

void *func_ov093_02298f4c(void *p)
{
    *(void **) p = &data_ov093_022998b8;
    func_020a8c38(p, &data_ov093_022998b8);
    return p;
}
