/* func_020f2500 @ 0x020f2500, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *receiver, int resource, int count);
extern int func_020f4038(void *receiver);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern unsigned char data_021fd1bc[];

void func_020f2500(void *receiver)
{
    func_020f4220(receiver, 0x2a824, 29);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}
