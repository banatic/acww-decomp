/* func_0203e6cc @ 0x0203e6cc, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x16];
    unsigned char unk_16;
} UnkStruct_0203e6cc;

int func_0203e6cc(UnkStruct_0203e6cc *s)
{
    if (s->unk_16 == 6) {
        return 1;
    } else {
        return 0;
    }
}
