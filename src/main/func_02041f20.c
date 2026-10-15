/* func_02041f20 @ 0x02041f20, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75ac;
extern int data_021c75cc;
extern void func_02001ba4(int);
extern void func_02001b6c(int);
extern int func_0205bfdc(int *);
extern void func_02001b34(int);
extern void func_02001afc(int);
extern void func_0203de68(void);

void func_02041f20(void)
{
    func_02001ba4(1);
    func_02001b6c(1);
    if (data_021c75ac & 1) {
        func_0205bfdc(&data_021c75cc);
        data_021c75ac &= ~1;
    }
    func_02001b34(4);
    func_02001afc(4);
    asm { mov r0, #0 }
    func_0203de68();
}
