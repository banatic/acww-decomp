/* func_ov130_02299d98 @ 0x02299d98, 0x24 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_02299dbc(void);
extern void func_ov130_02299c08(void *self);

struct unknown_ov130_02299d98 {
    int pad_00[3];
    int unk_0C;
};

int func_ov130_02299d98(struct unknown_ov130_02299d98 *self)
{
    if (self->unk_0C == 0) {
        return 0;
    }
    self->unk_0C = 0;
    func_ov130_02299dbc();
    func_ov130_02299c08(self);
    return 1;
}
