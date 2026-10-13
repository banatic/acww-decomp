/* func_ov107_0229cec4 @ 0x0229cec4, 0x44 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb8];
    unsigned char unk_B8;
} UnkStruct_0229cec4;

extern int func_ov107_0229d29c(void *p, int c);
extern int func_ov107_0229c2b4(void *p, int x);

int func_ov107_0229cec4(UnkStruct_0229cec4 *p)
{
    int r;
    r = func_ov107_0229d29c(p, p->unk_B8);
    if (func_ov107_0229c2b4(p, 0x10)) {
        r += 0x100;
    } else {
        if (func_ov107_0229c2b4(p, 8)) {
            r -= 0x100;
        }
    }
    r += 8;
    return r;
}
