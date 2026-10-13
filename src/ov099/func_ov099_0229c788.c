/* func_ov099_0229c788 @ 0x0229c788, 0x48 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

struct BigStruct {
    char pad_00[0x2907];
    unsigned char flag;
};

extern int func_ov099_0229cd70(struct BigStruct *p, unsigned char flag);
extern int func_ov099_0229c2ac(struct BigStruct *p, int value);

int func_ov099_0229c788(struct BigStruct *p)
{
    int result = func_ov099_0229cd70(p, p->flag);
    if (func_ov099_0229c2ac(p, 0x20) != 0) {
        result += 0x100;
    } else if (func_ov099_0229c2ac(p, 0x10) != 0) {
        result -= 0x100;
    }
    return result + 8;
}
