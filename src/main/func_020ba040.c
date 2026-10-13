/* func_020ba040 @ 0x020ba040, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002bd0(int a, unsigned char b, unsigned char c, unsigned char d, unsigned char e);

typedef struct {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020ba040;

void func_020ba040(UnkStruct_020ba040 *p)
{
    unsigned char c = (unsigned char) p->unk_08;
    unsigned char d = (unsigned char) p->unk_0C;
    func_02002bd0(p->unk_00, p->unk_04, c, c, d);
}
