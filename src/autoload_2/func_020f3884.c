/* func_020f3884 @ 0x020f3884, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int a, int b, int c);
extern void func_020f41f4(int a);
extern void func_020f4038(int a);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern char data_021fd1bc[];

void func_020f3884(int p)
{
    func_020f4220(p, 0x0002a824, 7);
    func_020f41f4(p);
    func_020f4038(p);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
