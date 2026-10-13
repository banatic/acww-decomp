/* func_020f36fc @ 0x020f36fc, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *, void *, int);
extern void func_020f41f4(void *);
extern void func_020f4038(void *);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
#define gUnknown1 ((unsigned char *) 0x0002a824)
extern unsigned char data_021fd1bc[];

void func_020f36fc(void *p)
{
    func_020f4220(p, gUnknown1, 9);
    func_020f41f4(p);
    func_020f4038(p);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
