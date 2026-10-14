/* func_02034ca0 @ 0x02034ca0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020051b0(void);
extern void __cxa_vec_cleanup(void *param1, int param2, int param3, void (*param4)(void));

extern unsigned char data_021c5204[];

void func_02034ca0(void)
{
    __cxa_vec_cleanup((void *) data_021c5204, 0x33, 2, func_020051b0);
}
