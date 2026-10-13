/* func_0208199c @ 0x0208199c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7c];
    unsigned short unk_7C;
} UnkStruct_0208199c;

void func_0208199c(UnkStruct_0208199c *s)
{
    s->unk_7C &= ~0x80;
}
