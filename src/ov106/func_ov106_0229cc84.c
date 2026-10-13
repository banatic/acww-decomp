/* func_ov106_0229cc84 @ 0x0229cc84, 0x44 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d170(void *, int);
extern int func_ov106_0229c364(void *, int);

typedef struct {
    char pad_00[0xb8];
    unsigned char b;
} UnkStruct_0229cc84;

int func_ov106_0229cc84(UnkStruct_0229cc84 *arg0)
{
    int ret;
    ret = func_ov106_0229d170(arg0, arg0->b);
    if (func_ov106_0229c364(arg0, 0x20) != 0) {
        ret += 0x100;
    } else if (func_ov106_0229c364(arg0, 0x10) != 0) {
        ret -= 0x100;
    }
    return ret + 8;
}
