/* func_020f2690 @ 0x020f2690, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, int a, int b);
extern void func_020f4038(void *p);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern unsigned char data_021fd1bc[0x100];

void func_020f2690(void *p)
{
    func_020f4220(p, 0x2a824, 0x1d);
    func_020f4038(p);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
