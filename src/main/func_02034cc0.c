/* func_02034cc0 @ 0x02034cc0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c519c[];
extern void func_020051b0(void);
extern void func_02138c48(void *a, int b, int c, void (*d)(void));

void func_02034cc0(void)
{
    func_02138c48(data_021c519c, 0x33, 2, func_020051b0);
}
