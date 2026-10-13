/* func_0208aef4 @ 0x0208aef4, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char *unk_04;
    unsigned char *unk_08;
} UnkStruct_0208aef4;
void func_0208aef4(UnkStruct_0208aef4 *p, unsigned char *a, unsigned char *b)
{
    p->unk_04 = a + 0x80;
    p->unk_08 = b + 0x60;
}
