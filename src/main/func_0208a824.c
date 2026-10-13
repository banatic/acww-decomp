/* func_0208a824 @ 0x0208a824, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    char pad_40[0x8];
    int unk_48;
    char pad_4C[0x4];
    int unk_50;
} UnkStruct_0208a824;

extern int func_0208aef0(UnkStruct_0208a824 *);

int func_0208a824(UnkStruct_0208a824 *s)
{
    int a;
    a = func_0208aef0(s);
    return s->unk_3C + a + s->unk_48 + s->unk_50;
}
