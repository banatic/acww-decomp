/* func_020f307c @ 0x020f307c, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int, int, int);
extern void func_020f41f4(int);
extern int func_020f4038(int);
extern void func_020eef70(int);
extern void NNS_SndHeapSaveState(void);
extern char data_021fd1bc[];

void func_020f307c(int arg)
{
    func_020f4220(arg, 0x232f4, 17);
    func_020f41f4(arg);
    func_020eef70(func_020f4038(arg));
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
