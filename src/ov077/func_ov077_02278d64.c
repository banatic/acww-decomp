/* func_ov077_02278d64 @ 0x02278d64, 0x18 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *);
extern char data_ov077_022797fc;

void *func_ov077_02278d64(void *p)
{
    func_0202eb70(p);
    *(void **) p = &data_ov077_022797fc;
    return p;
}
