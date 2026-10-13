/* func_ov077_02278d00 @ 0x02278d00, 0x2a bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035624(int);
extern void func_020356c4(int, int, int, int);

typedef struct UnkStruct_02278d00 {
    char pad_00[0xBC];
    unsigned char unk_BC;
} UnkStruct_02278d00;

void func_ov077_02278d00(UnkStruct_02278d00 *self)
{
    if (self->unk_BC == 0) {
        func_02035624(0x17);
        func_020356c4(0x18, 0x43, 0x7f, 1);
        self->unk_BC = 1;
    }
}
