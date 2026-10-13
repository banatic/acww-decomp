/* func_020bcdf8 @ 0x020bcdf8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int tag;
    unsigned char pad_04[0x60 - 4];
    unsigned int unk_60;
    unsigned char pad_64[0x10];
} UnkStruct_020bcdf8;

int func_020bcdf8(char *self, int kind)
{
    int result;
    UnkStruct_020bcdf8 *e;
    char *p, *end;
    unsigned int sub, f5, f0;

    result = 1;
    p = self + 0x14d8;
    end = self + 0x1abc;
    for (; p < end; p += 0x74) {
        e = (UnkStruct_020bcdf8 *) p;
        if (e->tag == 9) {
            sub = (e->unk_60 >> 8) & 3;
            f5 = ((e->unk_60 >> 0x1d) & 1) ? 1 : 0;
            f0 = ((e->unk_60 >> 0x1f) & 1) ? 1 : 0;
            if (sub == (unsigned int) kind) {
                result = 0;
                break;
            }
            if (f0 != 0) {
                if (f5 == 0) {
                    result = 0;
                    break;
                }
            }
        }
    }
    return result;
}
