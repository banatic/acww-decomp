/* func_ov052_02261108 @ 0x02261108, 0x20 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *p);
extern void func_020edb3c(void *p);
extern char data_ov052_02261eb0;

void *func_ov052_02261108(void *p)
{
    *(void **) p = &data_ov052_02261eb0;
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}
