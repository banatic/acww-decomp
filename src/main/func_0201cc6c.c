/* func_0201cc6c @ 0x0201cc6c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Global {
    char pad_00[0x64];
    int unk_64;
};
extern struct Global *data_020ccf94;
extern int func_02073dd4(struct Global *, int);

struct UnkStruct_0201cc6c {
    char pad_00[0x54];
    unsigned char unk_54;
    char pad_55;
    unsigned short unk_56;
};

void func_0201cc6c(struct UnkStruct_0201cc6c *unk, unsigned int idx, unsigned int count)
{
    struct Global *p = data_020ccf94;
    unsigned short val;

    if (func_02073dd4(p, p->unk_64) != 0 || idx >= 5) {
        return;
    }

    val = (unsigned short) (count * 1200);

    if (idx == unk->unk_54) {
        unk->unk_56 += val;
    } else {
        unk->unk_54 = idx;
        unk->unk_56 = val;
    }
}
