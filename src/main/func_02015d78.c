/* func_02015d78 @ 0x02015d78, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x4c];
    unsigned int unk_4C;
    unsigned int unk_50;
} UnkStruct_02015d78;

unsigned int func_02015d78(UnkStruct_02015d78 *r0, int r1)
{
    switch (r1) {
        case 0:
            return r0->unk_4C;
        case 1:
            return r0->unk_50;
        default:
            return 0;
    }
}
