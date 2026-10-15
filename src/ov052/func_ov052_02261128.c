/* func_ov052_02261128 @ 0x02261128, 0x18 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov052_02261eb0;
extern void *func_0202eb20(void *a);

void *func_ov052_02261128(void *p)
{
    *(void **) p = &data_ov052_02261eb0;
    func_0202eb20(p);
    return p;
}
