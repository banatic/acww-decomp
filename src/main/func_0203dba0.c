/* func_0203dba0 @ 0x0203dba0, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    unsigned char *buf;
    char pad_28[0x3c - 0x28];
    int unk_3C;
    int unk_40;
    unsigned char unk_44;
    char pad_45[0x50 - 0x45];
    unsigned char unk_50;
    char pad_51[3];
    int unk_54;
    int unk_58;
} UnkStruct_0203dba0;

void func_0203dba0(UnkStruct_0203dba0 *s)
{
    signed char a;
    signed char b;
    int n;

    a = (signed char) s->unk_3C;
    b = (signed char) (s->unk_3C >> 8);
    n = s->unk_40;
    if ((unsigned int) (0x200 - n) > 2) {
        if (s->unk_3C == 0xa && s->unk_50 != 0) {
            s->unk_58++;
            if (s->unk_58 == 1) {
                *(int *) (s->buf + 0x50c) = s->unk_54;
            }
        } else {
            *(s->buf + s->unk_40++ + 0x30c) = a;
            *(s->buf + s->unk_40++ + 0x30c) = b;
            if (s->unk_50 != 0) {
                s->unk_54++;
            }
        }
    } else {
        s->unk_44 = 0;
    }
}
