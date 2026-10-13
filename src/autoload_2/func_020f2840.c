/* func_020f2840 @ 0x020f2840, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int a, int b, int c);
extern void func_020f41a4(int a, int b);
extern void func_020f4038(int a);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);

extern unsigned char data_021fd1bc[];

void func_020f2840(int arg)
{
    func_020f4220(arg, 0, 0x1b);
    func_020f41a4(arg, 3);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
