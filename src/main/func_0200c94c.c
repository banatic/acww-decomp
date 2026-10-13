/* func_0200c94c @ 0x0200c94c, 0x8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short unk_00;
    short pad_02;
    int unk_04;
    int unk_08;
} UnkStruct_0200c94c;
void func_0200c94c(UnkStruct_0200c94c *p, int a, int b, int c)
{
    p->unk_00 = (short) a;
    p->unk_04 = b;
    p->unk_08 = c;
}
