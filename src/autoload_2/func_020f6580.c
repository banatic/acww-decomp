/* func_020f6580 @ 0x020f6580, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f6580 {
    char pad_00[0x28];
    int x;
};
extern void NNS_SndHeapLoadState(int, int);
extern void func_0210e198(int, int);

extern unsigned char data_021fd1bc[];

void func_020f6580(int a, int b)
{
    struct UnkStruct_020f6580 *p = (struct UnkStruct_020f6580 *) data_021fd1bc;
    int v = p->x;
    NNS_SndHeapLoadState(v, 0);
    func_0210e198(b, v);
}
