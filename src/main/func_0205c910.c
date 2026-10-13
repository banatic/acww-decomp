/* func_0205c910 @ 0x0205c910, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern void func_020e9fc8(int arg);
#pragma thumb

extern int data_021c9b04;

void func_0205c910(void)
{
    func_020e9fc8(data_021c9b04);
    data_021c9b04 = 0;
}
