/* func_020f0f48 @ 0x020f0f48, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_020f0f48 {
    unsigned char pad_00[0x71];
    unsigned char unk_71;
} UnkStruct_020f0f48;
void func_020f0f48(UnkStruct_020f0f48 *self, int v)
{
    switch (v) {
        case 1:
            self->unk_71 = 1;
            return;
        default:
            self->unk_71 = 0;
            return;
    }
}
