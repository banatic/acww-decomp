/* func_ov054_02261fb0 @ 0x02261fb0, 0x18 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *);
extern char data_ov054_02263004[];

void *func_ov054_02261fb0(void *p)
{
    func_0202eb70(p);
    *(unsigned int *) p = (unsigned int) data_ov054_02263004;
    return p;
}
