/* func_ov002_022087d4 @ 0x022087d4, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208874(void *p);
extern char data_ov002_0220baf4;

void *func_ov002_022087d4(void *p)
{
    func_ov002_02208874(p);
    *(void **) p = (void *) &data_ov002_0220baf4;
    return p;
}
