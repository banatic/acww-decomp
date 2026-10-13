/* func_ov003_02217a6c @ 0x02217a6c, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02217a6c {
    unsigned char b;
    char pad_01;
    short s;
};

extern void func_ov003_02217bf0(int base, struct UnkStruct_02217a6c *out1, int *out2, int *out3, short *out4);
extern void func_ov003_02217c5c(int p1, int sel, unsigned char lowNib, int v14, int v18, short s, int const6, int p2);

void func_ov003_02217a6c(int p1, int p2)
{
    struct UnkStruct_02217a6c local;
    int v14, v18;
    int sel;
    int key;

    func_ov003_02217bf0(p1 + 0x8f0, &local, &v14, &v18, &local.s);

    key = local.b & 0xf0;
    switch (key) {
        case 0x00:
            sel = 0x38;
            break;
        case 0x10:
            sel = 0x39;
            break;
        case 0x20:
            sel = 0x10;
            break;
        default:
            sel = 2;
            break;
    }

    func_ov003_02217c5c(p1, sel, local.b & 0x0f, v14, v18, local.s, 6, p2);
}
