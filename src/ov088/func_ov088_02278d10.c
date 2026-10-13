/* func_ov088_02278d10 @ 0x02278d10, 0x18 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *);
extern char data_ov088_02279c58;

void *func_ov088_02278d10(void *p)
{
    func_0202eb70(p);
    *(void **) p = &data_ov088_02279c58;
    return p;
}
