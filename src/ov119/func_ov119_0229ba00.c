/* func_ov119_0229ba00 @ 0x0229ba00, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov090_022990b8(int index);

struct UnkStruct_0229ba00 {
    char pad_00[0xA0];
    unsigned char kind;
};

int func_ov119_0229ba00(struct UnkStruct_0229ba00 *p)
{
    unsigned char v = p->kind;
    if (v <= 7) {
        return 0x20;
    }
    if (v >= 14 && v <= 21) {
        return func_ov090_022990b8(v - 14);
    }
    if (v >= 8 && v <= 13) {
        return 0xD6;
    }
    if (v == 22) {
        return 0xDB;
    }
    return 0x80;
}
