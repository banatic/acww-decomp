/* func_0205c1e0 @ 0x0205c1e0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c9ab8;
extern void func_020e9fc8(void *);

void func_0205c1e0(void)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (data_021c9ab8)) != 0) {
        func_020e9fc8(condition_value0);
    }
    data_021c9ab8 = 0;
}
