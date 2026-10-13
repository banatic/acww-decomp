/* func_0208b6ec @ 0x0208b6ec, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fd10(void);
extern int FX_MulFunc(int a, int b);

struct UnkStruct_0208b6ec {
    char pad_00[0x24];
    int unk_24;
};

void func_0208b6ec(struct UnkStruct_0208b6ec *param)
{
    int v1;
    int v2;
    int v3;

    v1 = func_0206fd10();
    v2 = FX_MulFunc(0, v1);
    v3 = FX_MulFunc(0x000c0000, 0x00001000 - v1);
    param->unk_24 = (v2 + v3) >> 12;
}
