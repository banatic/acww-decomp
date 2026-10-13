/* func_020550b8 @ 0x020550b8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[2];
    unsigned int unk_08;
} UnkStruct_020550b8;

unsigned short func_020550b8(int param, UnkStruct_020550b8 *p)
{
    unsigned short v = p->unk_04;

    if (param == 0 || param == 2) {
        unsigned int w = p->unk_08;

        if (w & 2) {
            return v;
        }
        if (w & 1) {
            v = (unsigned short) (v - 1);
        }
    }
    return v;
}
