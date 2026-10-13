/* func_020f2ed4 @ 0x020f2ed4, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int, int, int);
extern void func_020f41f4(int);
extern void func_020f4038(int);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern unsigned char data_021fd1bc[0x63];

void func_020f2ed4(int arg)
{
    func_020f4220(arg, 0x2a824, 19);
    func_020f41f4(arg);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
