/* func_ov003_0220f658 @ 0x0220f658, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x7d6 - 0x90];
    short unk_7D6;
} UnkStruct_0220f658;

typedef struct {
    short v[4];
} LocalVec;

extern int func_020113e0(LocalVec *vec, short value);
extern void func_020110a0(void *object, short *values);

void func_ov003_0220f658(UnkStruct_0220f658 *self)
{
    LocalVec vec;
    vec.v[0] = self->unk_8E;
    func_020113e0(&vec, self->unk_7D6);
    func_020110a0((void *) (self), (short *) (&vec));
}
