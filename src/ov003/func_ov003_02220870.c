/* func_ov003_02220870 @ 0x02220870, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *ptr);
extern char data_ov003_02239b2c[];
extern char data_020da13c[];

void *func_ov003_02220870(void *ptr)
{
    *(void *volatile *) ptr = data_ov003_02239b2c;
    *(void *volatile *) ptr = data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
