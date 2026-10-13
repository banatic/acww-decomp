/* func_0204f9ec @ 0x0204f9ec, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204fa4c(unsigned char);
extern void func_0204fa5c(void *, unsigned char);

struct UnkStruct_0204f9ec {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned int unk_04;
    unsigned int unk_08;
};

void func_0204f9ec(struct UnkStruct_0204f9ec *p)
{
    unsigned char c;
    char buffer[44];
    c = p->unk_00;
    func_0204fa4c(c);
    func_0204fa5c(buffer, c);
    p->unk_00 = 0xFF;
    p->unk_01 = 0;
    p->unk_02 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
}
