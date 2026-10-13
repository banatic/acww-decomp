/* func_0203c030 @ 0x0203c030, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203c40c(void *s, short val);

typedef struct {
    char pad_00[0x1b0];
    int unk_1B0;
    int unk_1B4;
    int unk_1B8;
    char pad_1BC[0xc];
    short unk_1C8;
} UnkStruct_0203c030;

void func_0203c030(UnkStruct_0203c030 *s)
{
    s->unk_1B0 = 0x1548;
    s->unk_1B4 = 0xf6;
    s->unk_1B8 = 0x0003e800;
    func_0203c40c(s, s->unk_1C8);
}
