/* func_020534ac @ 0x020534ac, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020530b0(void);
extern void func_02138c48(void *param1, int param2, int param3, void (*param4)(void));

extern unsigned char data_021c884c[];

void func_020534ac(void)
{
    func_02138c48((void *) data_021c884c, 6, 0x48, func_020530b0);
}
