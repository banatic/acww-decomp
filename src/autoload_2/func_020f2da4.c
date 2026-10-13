/* func_020f2da4 @ 0x020f2da4, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *arg, int data, int size);
extern void func_020f41f4(void *arg);
extern void func_020f4038(void *arg);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern char data_021fd1bc[];

void func_020f2da4(void *arg)
{
    func_020f4220(arg, 0x245c0, 20);
    func_020f41f4(arg);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
