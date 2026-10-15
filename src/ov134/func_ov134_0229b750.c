/* func_ov134_0229b750 @ 0x0229b750, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229b5ac(void *, unsigned char, int, int, unsigned char, int, int);

struct unknown {
    char pad_00[0xA3];
    unsigned char unk_A3;
    char pad_A4[0xBA - 0xA3 - 1];
    unsigned char unk_BA;
};

void func_ov134_0229b750(struct unknown *p)
{
    func_ov134_0229b5ac(p, p->unk_A3, 0x1B6, 3, p->unk_BA, 0xF, 0);
}
