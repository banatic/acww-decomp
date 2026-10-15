/* func_020f3490 @ 0x020f3490, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *receiver, int resource, int count);
extern int func_020f4038(void *receiver);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern unsigned char data_021fd1bc[];
extern void func_020f41f4(void *receiver);
extern void func_020f4178(void *receiver);
extern void func_020f4130(void *receiver);

void func_020f3490(void *receiver)
{
    func_020f4220(receiver, 0x232f4, 12);
    func_020f41f4(receiver);
    func_020f4178(receiver);
    func_020f4130(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}
