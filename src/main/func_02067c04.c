/* func_02067c04 @ 0x02067c04, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206bd24(void *ptr);
extern void NNS_G2dResetEntityPaletteTable(void *ptr);

typedef struct {
    char pad_00[0x13b8];
    char unk_13B8;
} UnkStruct_02067c04;

void func_02067c04(UnkStruct_02067c04 *arg)
{
    func_0206bd24(&arg->unk_13B8);
    NNS_G2dResetEntityPaletteTable(arg);
}
