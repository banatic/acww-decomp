/* func_ov046_0226086c @ 0x0226086c, 0x38 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void *, int);

typedef struct {
    char pad_00[0xdc];
    int unk_DC;
} UnkStruct_0226086c;

void func_ov046_0226086c(UnkStruct_0226086c *p, int r1)
{
    if (r1 == 0) {
        int ret = func_020b1558(p, r1);
        if (ret < 0x10) {
            p->unk_DC = 0x18;
        } else {
            p->unk_DC = 7;
        }
    } else if (r1 == 1) {
        p->unk_DC = 0x30;
    } else {
        p->unk_DC = 2;
    }
}
