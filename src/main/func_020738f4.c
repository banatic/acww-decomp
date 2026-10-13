/* func_020738f4 @ 0x020738f4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x6C];
    unsigned char unk_6C;
} UnkStruct_020738f4;

void func_020738f4(UnkStruct_020738f4 *s, unsigned int val)
{
    if (val > 4) {
        s->unk_6C = 0;
    } else {
        s->unk_6C = val;
    }
}
