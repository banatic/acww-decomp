/* func_020ba09c @ 0x020ba09c, 0x8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
    unsigned char pad_05[3];
    int unk_08;
} UnkStruct_020ba09c;
void func_020ba09c(UnkStruct_020ba09c *p, int a, int b, int c)
{
    p->unk_00 = a;
    p->unk_04 = (unsigned char) b;
    p->unk_08 = c;
}
