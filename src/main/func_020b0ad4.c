/* func_020b0ad4 @ 0x020b0ad4, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0ae0(void *);

struct UnkStruct_020b0ad4 {
    int unk_00;
    int unk_04;
    void *unk_08;
};

void func_020b0ad4(struct UnkStruct_020b0ad4 *self)
{
    func_020b0ae0(self->unk_08);
}
