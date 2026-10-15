/* func_020f2784 @ 0x020f2784, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *receiver, int resource, int count);
extern void func_020f41a4(void *receiver, int count);
extern void func_020f4080(void *receiver);
extern int func_020f4038(void *receiver);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern int func_020f1d84(void *receiver, int sound);
extern void func_020f1004(void *receiver);
extern void func_020f4318(unsigned char *receiver);
extern unsigned char data_021fd1bc[];

void func_020f2784(void *receiver)
{
    func_020f4220(receiver, 0, 28);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
    func_020f1004(data_021fd1bc);
}
