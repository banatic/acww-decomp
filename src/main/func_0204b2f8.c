/* func_0204b2f8 @ 0x0204b2f8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
} UnkStruct_0204b2f8;

int func_0204b2f8(UnkStruct_0204b2f8 *s)
{
    int r;
    unsigned short v;

    r = 0;
    v = s->unk_00;

    if (v >= 0x1144 && v <= 0x1187) {
        r = 1;
    }

    if (r) {
        return 1;
    } else {
        return 0;
    }
}
