/* func_0209bd5c @ 0x0209bd5c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
    unsigned char unk_0B;
} UnkStruct_0209bd5c;

void func_0209bd5c(UnkStruct_0209bd5c *p)
{
    p->unk_0A = 0x16;
    p->unk_08 = 0xfff1;
    p->unk_0B &= ~0x1F;
    p->unk_0B &= ~0xE0;
}
