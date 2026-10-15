/* func_ov079_02278c38 @ 0x02278c38, 0x14 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014d04(void *);

struct UnkStruct_02278c38 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

void func_ov079_02278c38(struct UnkStruct_02278c38 *self)
{
    if (self->unk_1E == 0xf) {
        func_02014d04(self);
    }
}
