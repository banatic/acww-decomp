/* func_ov103_0229c820 @ 0x0229c820, 0x48 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229ccb4(void *p, int b);
extern int func_ov103_0229c2f4(void *p, int mode);

struct Ts {
    char pad_00[0x2da4];
    unsigned char unk_2DA4;
};

int func_ov103_0229c820(struct Ts *p)
{
    int val;

    val = func_ov103_0229ccb4(p, p->unk_2DA4);
    if (func_ov103_0229c2f4(p, 0x20) != 0) {
        val += 0x100;
    } else if (func_ov103_0229c2f4(p, 0x10) != 0) {
        val -= 0x100;
    }
    val += 8;
    return val;
}
