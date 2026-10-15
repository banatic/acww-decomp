/* func_020f3eb4 @ 0x020f3eb4, 0x60 bytes, ARM, module autoload_2
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

void func_020f3eb4(void *receiver)
{
    func_020f4220(receiver, 0x21ef8, 1);
    func_020f41a4(receiver, 3);
    func_020f4080(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    func_020f1d84(data_021fd1bc, 0x8f);
    data_021fd1bc[0x62] = 0;
}
