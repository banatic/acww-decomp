/* func_020f3eb4 @ 0x020f3eb4, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int a, int b, int c);
extern void func_020f41a4(int a, int b);
extern void func_020f4080(int a);
extern void func_020f4038(int a);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern void func_020f1d84(int a, int b);
#define global_21ef8 (*(int *) 0x00021ef8)
extern unsigned char data_021fd1bc[];

void func_020f3eb4(int arg)
{
    func_020f4220(arg, (int) &global_21ef8, 1);
    func_020f41a4(arg, 3);
    func_020f4080(arg);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    func_020f1d84((int) data_021fd1bc, 0x8f);
    data_021fd1bc[0x62] = 0;
}
