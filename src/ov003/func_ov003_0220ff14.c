/* func_ov003_0220ff14 @ 0x0220ff14, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220ff14 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x750];
    short unk_7E0;
};

extern int func_020113e0(short *p, short val);
extern void func_020110a0(void *object, short *values);

void func_ov003_0220ff14(struct UnkStruct_0220ff14 *self)
{
    short local;
    local = self->unk_8E;
    func_020113e0(&local, self->unk_7E0);
    func_020110a0((void *) (self), (short *) (&local));
}
