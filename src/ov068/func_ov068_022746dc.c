/* func_ov068_022746dc @ 0x022746dc, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02277dc0;
extern void func_0202eb20(void *a, void *b);
extern void func_020edb3c(void *a);

void *func_ov068_022746dc(void *p)
{
    *(void **) p = &data_ov068_02277dc0;
    func_0202eb20(p, &data_ov068_02277dc0);
    func_020edb3c(p);
    return p;
}
