/* func_ov045_022604f4 @ 0x022604f4, 0x18 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov045_02261414;
extern void func_020a8c38(void *);

void *func_ov045_022604f4(void *p)
{
    *(void **) p = &data_ov045_02261414;
    func_020a8c38(p);
    return p;
}
