/* func_020f2a94 @ 0x020f2a94, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int, int, int);
extern void func_020f41f4(int);
extern void func_020f4038(int);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);

struct GlobalData {
    char pad_00[0x62];
    unsigned char flag;
};
extern struct GlobalData data_021fd1bc;

void func_020f2a94(int arg)
{
    func_020f4220(arg, 0x000245c0, 0x18);
    func_020f41f4(arg);
    func_020f4038(arg);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc.flag = 0;
}
