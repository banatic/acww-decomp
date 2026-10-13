/* func_ov094_0229afe0 @ 0x0229afe0, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov094_0229bf90[];
extern void func_ov094_0229b0f8(char *);

struct UnkStruct_0229afe0 {
    char *unk_00;
    char pad_04[0x180];
    char sub;
};

struct UnkStruct_0229afe0 *func_ov094_0229afe0(struct UnkStruct_0229afe0 *self)
{
    self->unk_00 = data_ov094_0229bf90;
    func_ov094_0229b0f8(&self->sub);
    return self;
}
