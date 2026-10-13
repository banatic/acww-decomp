/* func_0208a944 @ 0x0208a944, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct0908A944 {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    char pad_3C[0x0c];
    int unk_48;
    int unk_4C;
    char pad_50[0x09];
    unsigned char unk_59;
    unsigned char unk_5A;
} UnkStruct_0208a944;

void func_0208a944(UnkStruct_0208a944 *p)
{
    if (p->unk_59 != 0) {
        p->unk_38 = 1;
        p->unk_48 = 0;
        p->unk_4C = 0;
    } else {
        p->unk_38 = 3;
        p->unk_48 = -5;
        p->unk_4C = (p->unk_5A == 0) ? 5 : -5;
    }
    p->unk_34 = 1;
}
