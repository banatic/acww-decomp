/* func_02092110 @ 0x02092110, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern void func_02094e04(int, int);
struct Global {
    char pad_00[0x10];
    short unk_10;
};
extern struct Global data_021d5658;

void func_02092110(int param)
{
    short s = (short) FX_MulFunc(0x1e66, data_021d5658.unk_10);
    s = (short) (s + 0xb33);
    func_02094e04(param, s);
}
