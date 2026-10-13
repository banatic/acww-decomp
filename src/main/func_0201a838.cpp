/* func_0201a838 @ 0x0201a838, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201a838;
typedef void (UnkStruct_0201a838::*PMF)(unsigned char *);
extern PMF data_021c1794[6];

struct UnkStruct_0201a838_2 {
    unsigned char unk_00;
    unsigned char pad_01[0x17];
    unsigned char unk_18;
};

extern "C" void func_0201a838(UnkStruct_0201a838_2 *p, unsigned char *base);

void func_0201a838(UnkStruct_0201a838_2 *p, unsigned char *base)
{
    if (p->unk_18 == 0 && p->unk_00 < 6) {
        UnkStruct_0201a838 *obj = (UnkStruct_0201a838 *) (base + 0x3b0);
        (obj->*data_021c1794[p->unk_00])(base);
    }
}
