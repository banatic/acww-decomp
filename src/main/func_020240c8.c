/* func_020240c8 @ 0x020240c8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209b920(int);
extern void func_02078630(int);

typedef struct UnkStruct_020240c8 {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_020240c8;

typedef struct UnkStruct_020240c8_2 {
    unsigned char pad_00[0x100];
    UnkStruct_020240c8 *unk_100;
    unsigned char pad_104[0x60];
    int unk_164;
} UnkStruct_020240c8_2;

void func_020240c8(UnkStruct_020240c8_2 *arg)
{
    func_0209b920(arg->unk_164);
    func_02078630(arg->unk_100->unk_830);
}
