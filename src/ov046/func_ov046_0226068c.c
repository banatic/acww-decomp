/* func_ov046_0226068c @ 0x0226068c, 0x54 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC4];
    unsigned char unk_C4;
    unsigned char unk_C5;
    unsigned char unk_C6;
    char pad_C7[0xDC - 0xC7];
    int unk_DC;
} UnkStruct_0226068c;

extern int func_020b1558(void);
extern int func_ov046_022610fc(UnkStruct_0226068c *p);

void func_ov046_0226068c(UnkStruct_0226068c *p, int cond)
{
    int x = func_020b1558();
    p->unk_C5 = 0x10 - x;
    p->unk_C4 = 0;
    if (cond == 0) {
        p->unk_C6 = 2;
        p->unk_DC = 0x1e;
    } else {
        int y = func_020b1558();
        if (y < 0x10) {
            p->unk_DC = 0x25;
        } else {
            p->unk_DC = func_ov046_022610fc(p);
        }
    }
}
