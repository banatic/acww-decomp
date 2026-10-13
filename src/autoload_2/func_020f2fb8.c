/* func_020f2fb8 @ 0x020f2fb8, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, int a, int b);
extern void func_020f41f4(void *p);
extern void func_020f4038(void *p);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern unsigned char data_021fd1bc[];

void func_020f2fb8(void *arg)
{
    func_020f4220(arg, 0x245c0, 0x12);
    func_020f41f4(arg);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
