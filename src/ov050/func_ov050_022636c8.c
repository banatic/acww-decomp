/* func_ov050_022636c8 @ 0x022636c8, 0x18 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *p);
extern char data_ov050_02265b14;

void *func_ov050_022636c8(void *p)
{
    func_0202eb70(p);
    *(void **) p = (void *) &data_ov050_02265b14;
    return p;
}
