/* func_ov113_02299a80 @ 0x02299a80, 0x24 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a80 {
    char pad_00[0x9d];
    unsigned char unk_9D;
    unsigned char unk_9E;
};

extern int func_02077ec4(void);

void func_ov113_02299a80(struct UnkStruct_02299a80 *self)
{
    self->unk_9D = func_02077ec4();
    self->unk_9E = (0xf - self->unk_9D) << 2;
}
