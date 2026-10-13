/* func_ov048_022623f0 @ 0x022623f0, 0x3c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *data_ov048_02263d20;
extern int func_02073918(void *a, int b);
extern void func_0206844c(void *a, char *b, void *c);

struct UnkStruct_022623f0 {
    char pad_00[0x40];
    void *unk_40;
};

void func_ov048_022623f0(struct UnkStruct_022623f0 *p)
{
    char buf[8];

    buf[0] = func_02073918(data_020ccf94, 0) ? 0x10 : 0xf;
    func_0206844c(p->unk_40, buf, data_ov048_02263d20);
}
