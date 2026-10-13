/* func_ov068_0226e1fc @ 0x0226e1fc, 0x14 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226e1fc {
    char pad_00[0x654];
    int unk_654;
};

int func_ov068_0226e1fc(struct UnkStruct_0226e1fc *self)
{
    int ret = 0;
    if (self->unk_654 == 0) {
        ret = 1;
    }
    return ret;
}
