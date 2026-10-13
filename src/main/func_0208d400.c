/* func_0208d400 @ 0x0208d400, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x50];
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
} UnkStruct_0208d400;

void func_0208d400(UnkStruct_0208d400 *s)
{
    int zero = 0;
    s->unk_50 = zero;
    s->unk_54 = zero;
    s->unk_5C = ~zero;
    s->unk_58 = zero;
}
