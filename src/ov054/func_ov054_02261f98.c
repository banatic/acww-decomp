/* func_ov054_02261f98 @ 0x02261f98, 0x18 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *obj);
extern char data_ov054_02263004;

void *func_ov054_02261f98(void *obj)
{
    void *val = &data_ov054_02263004;

    *(void **) obj = val;
    func_0202eb20(obj);
    return obj;
}
