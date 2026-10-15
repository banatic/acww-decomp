/* func_ov003_0221d038 @ 0x0221d038, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221d048(void *state);

struct func_ov003_0221d038_struct {
    char pad_00[0x1c];
    void (*fp)(void *);
    char pad_20[0x70];
    unsigned char unk_90;
};

void func_ov003_0221d038(struct func_ov003_0221d038_struct *obj)
{
    obj->fp = func_ov003_0221d048;
    obj->unk_90 = 2;
}
