/* func_0206eac0 @ 0x0206eac0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f70d0(void *p);

struct S0206eac0 {
    char pad_00[0x14];
    void *unk_14;
};

void *func_0206eac0(struct S0206eac0 *self)
{
    func_020f70d0(&self->unk_14);
    func_020f70d0(self);
    return self;
}
