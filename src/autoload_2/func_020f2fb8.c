/* func_020f2fb8 @ 0x020f2fb8, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *receiver, int resource, int count);
extern int func_020f4038(void *receiver);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern unsigned char data_021fd1bc[];
extern void func_020f41f4(void *receiver);

void func_020f2fb8(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 18);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}
