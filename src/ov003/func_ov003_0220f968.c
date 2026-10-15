/* func_ov003_0220f968 @ 0x0220f968, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220f968 {
    unsigned char pad_00[0x8e];
    short unk_8E;
    unsigned char pad_90[0x74c];
    short unk_7DC;
};

extern int func_020113e0(short *a, int b);
extern void func_020110a0(void *object, short *values);

void func_ov003_0220f968(struct UnkStruct_0220f968 *self)
{
    short local;

    local = self->unk_8E;
    func_020113e0(&local, self->unk_7DC);
    func_020110a0((void *) (self), (short *) (&local));
}
