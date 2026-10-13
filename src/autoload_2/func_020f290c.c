/* func_020f290c @ 0x020f290c, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f4220(int a, int b, int c);
extern int func_020f41f4(int a);
extern int func_020f4038(int a);
extern int func_020eef70(int a);
extern int NNS_SndHeapSaveState(int a);
extern char data_021fd1bc[];

void func_020f290c(int arg0)
{
    func_020f4220(arg0, 0x245c0, 26);
    func_020f41f4(arg0);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(arg0)));
    data_021fd1bc[0x62] = 0;
}
