/* func_020f3a0c @ 0x020f3a0c, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4318(void);
extern void func_020f1d84(int, int);
extern void func_020f4038(int);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);

extern unsigned char data_021fd1bc[];

void func_020f3a0c(int r4)
{
    func_020f4318();
    func_020f1d84((unsigned int) data_021fd1bc, 0x90);
    func_020f4038(r4);
    func_020eef70();
    NNS_SndHeapSaveState();
    *(unsigned char *) (r4 + 0x1c) = 1;
}
