/* func_02041b74 @ 0x02041b74, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001b34(int);
extern void func_02001afc(int);
extern void func_0203de68(void);

void func_02041b74(void)
{
    func_02001b34(4);
    func_02001afc(4);
    asm { mov r0, #0 }
    func_0203de68();
}
