/* func_020382b8 @ 0x020382b8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020382b8 UnkStruct_020382b8;
struct UnkStruct_020382b8 {
    unsigned char pad_00[0xbc];
    int unk_BC;
    unsigned char pad_C0[8];
    unsigned char unk_C8;
};

extern void func_0203837c(UnkStruct_020382b8 *obj);

void func_020382b8(UnkStruct_020382b8 *arg)
{
    arg->unk_BC = 1;
    arg->unk_C8 = 0;
    func_0203837c(arg);
}
