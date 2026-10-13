/* func_0208a890 @ 0x0208a890, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    int unk_38;
    unsigned char pad_3C[0x1D];
    unsigned char unk_59;
} UnkStruct_0208a890;

void func_0208a890(UnkStruct_0208a890 *s)
{
    if (s->unk_59 != 0) {
        s->unk_38 = 1;
    } else {
        s->unk_38 = 2;
    }
    s->unk_34 = 3;
}
