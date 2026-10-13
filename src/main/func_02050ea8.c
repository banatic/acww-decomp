/* func_02050ea8 @ 0x02050ea8, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050ef4(void *);
extern int func_02050edc(void *);

typedef struct {
    unsigned char unk_00[0x38];
    unsigned char unk_38;
    unsigned char pad_39;
    unsigned char unk_3A;
    unsigned char pad_3B;
    unsigned char unk_3C;
} UnkStruct_02050ea8;

unsigned char func_02050ea8(UnkStruct_02050ea8 *s)
{
    unsigned char result;

    result = s->unk_38;
    if (func_02050ef4(s)) {
        result = s->unk_3A;
    } else {
        if (func_02050edc(s)) {
            result = s->unk_3C;
        }
    }
    return result;
}
