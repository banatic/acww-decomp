/* func_02041b90 @ 0x02041b90, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203de6c(void);
extern void func_02001b54(int);
extern void func_02001b1c(int);
extern void func_02041a9c(void);
extern void func_02001aac(int);

void func_02041b90(void)
{
    asm { mov r0, #0 }
    func_0203de6c();
    func_02001b54(0x10);
    func_02001b1c(0);
    func_02041a9c();
    func_02001aac(~0xf);
}
