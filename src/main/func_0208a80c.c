/* func_0208a80c @ 0x0208a80c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[8];
    int unk_4C;
} UnkStruct_0208a80c;

extern int func_0208aeec(UnkStruct_0208a80c *);

int func_0208a80c(UnkStruct_0208a80c *s)
{
    int r = func_0208aeec(s);
    int b = s->unk_4C;
    int a = s->unk_40;
    return b + (a + r);
}
