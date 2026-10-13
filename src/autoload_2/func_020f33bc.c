/* func_020f33bc @ 0x020f33bc, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int a, int b, int c);
extern void func_020f41f4(int a);
extern void func_020f4178(int a);
extern void func_020f4130(int a);
extern int func_020f4038(int a);
extern int func_020eef70(int a);
extern void NNS_SndHeapSaveState(int a);
extern unsigned char data_021fd1bc[];

void func_020f33bc(int param)
{
    func_020f4220(param, 0x232f4, 13);
    func_020f41f4(param);
    func_020f4178(param);
    func_020f4130(param);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(param)));
    data_021fd1bc[0x62] = 0;
}
