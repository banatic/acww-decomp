/* func_020f29d0 @ 0x020f29d0, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, void *q, int n);
extern void func_020f41f4(void *p);
extern void func_020f4038(void *p);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
#define g_245c0 ((int *) 0x000245c0)
extern unsigned char data_021fd1bc[];

void func_020f29d0(void *p)
{
    func_020f4220(p, g_245c0, 0x19);
    func_020f41f4(p);
    func_020f4038(p);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
