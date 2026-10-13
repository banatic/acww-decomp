/* func_0204622c @ 0x0204622c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char flag : 3;
    unsigned char type : 5;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char pad_03[7];
    unsigned short unk_0A;
    unsigned short unk_0C;
} UnkStruct_0204622c;

extern void func_020464d4(UnkStruct_0204622c *p);
extern void func_0204629c(UnkStruct_0204622c *p);

void func_0204622c(UnkStruct_0204622c *p)
{
    switch (p->type) {
        case 4:
        case 22:
        case 25:
            func_020464d4(p);
            p->unk_01 |= 0x80;
            p->unk_02 &= ~1;
            break;
        case 10:
            func_020464d4(p);
            p->unk_01 |= 0x80;
            p->unk_02 &= ~1;
            p->unk_0A = p->unk_0C;
            p->unk_01 = (p->unk_01 & ~3) | 1;
            break;
        default:
            func_0204629c(p);
            break;
    }
}
