/* func_020f3564 @ 0x020f3564, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int arg, char *ptr, int n);
extern void func_020f41f4(int arg);
extern int func_020f4038(int arg);
extern int func_020eef70(int arg);
extern void NNS_SndHeapSaveState(int arg);
#define G1 (*(char *) 0x0002a824)
extern unsigned char data_021fd1bc[];

void func_020f3564(int arg)
{
    func_020f4220(arg, &G1, 11);
    func_020f41f4(arg);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(arg)));
    data_021fd1bc[0x62] = 0;
}
