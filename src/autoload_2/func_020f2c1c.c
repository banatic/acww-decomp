/* func_020f2c1c @ 0x020f2c1c, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(const void *, const void *, int);
extern void func_020f41f4(const void *);
extern void func_020f4038(const void *);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
#define someTable_245c0 ((const char *) 0x000245c0)
extern unsigned char data_021fd1bc[];

void func_020f2c1c(void *arg)
{
    func_020f4220(arg, someTable_245c0, 22);
    func_020f41f4(arg);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
