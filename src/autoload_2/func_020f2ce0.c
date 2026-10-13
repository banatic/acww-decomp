/* func_020f2ce0 @ 0x020f2ce0, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, const void *data, int len);
extern void func_020f41f4(void *p);
extern int func_020f4038(void *p);
extern int func_020eef70(int);
extern void NNS_SndHeapSaveState(int);
extern unsigned char data_021fd1bc[];

void func_020f2ce0(void *p)
{
    func_020f4220(p, (void *) 0x245c0, 21);
    func_020f41f4(p);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(p)));
    data_021fd1bc[0x62] = 0;
}
