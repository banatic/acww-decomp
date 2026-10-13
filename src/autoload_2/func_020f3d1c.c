/* func_020f3d1c @ 0x020f3d1c, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int, int, int);
extern void func_020f41a4(int, int);
extern void func_020f4038(int);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern void func_020f1d84(void *, int);

struct GStruct {
    unsigned char pad_00[0x62];
    unsigned char byte;
};

extern struct GStruct data_021fd1bc;

void func_020f3d1c(int param)
{
    func_020f4220(param, 0x1f340, 2);
    func_020f41a4(param, 2);
    func_020f4038(param);
    func_020eef70();
    NNS_SndHeapSaveState();
    func_020f1d84(&data_021fd1bc, 0x8f);
    data_021fd1bc.byte = 0;
}
