/* func_ov004_0222da90 @ 0x0222da90, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222daa0(void);

struct func_ov003_0221d038_struct {
    char pad_00[0x1c];
    void (*fp)(void);
    char pad_20[0x70];
    unsigned char unk_90;
};

void func_ov004_0222da90(struct func_ov003_0221d038_struct *obj)
{
    obj->fp = func_ov004_0222daa0;
    obj->unk_90 = 2;
}
