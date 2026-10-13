/* func_ov100_0229cc70 @ 0x0229cc70, 0x48 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2921];
    unsigned char unk_2921;
} UnkStruct_0229cc70;

extern int func_ov100_0229d42c(void *, unsigned char);
extern int func_ov100_0229c2c0(void *, int);

int func_ov100_0229cc70(UnkStruct_0229cc70 *p)
{
    int r4;
    r4 = func_ov100_0229d42c(p, p->unk_2921);
    if (func_ov100_0229c2c0(p, 0x20) != 0) {
        r4 += 0x100;
    } else {
        if (func_ov100_0229c2c0(p, 0x10) != 0) {
            r4 -= 0x100;
        }
    }
    r4 += 8;
    return r4;
}
