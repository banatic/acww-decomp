/* func_ov068_0226cc00 @ 0x0226cc00, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226cbe4(void *a, int b);

struct UnkStruct_0226cc00 {
    char pad_00[0x24];
    int unk_24;
};

int func_ov068_0226cc00(struct UnkStruct_0226cc00 *this)
{
    if (func_ov068_0226cbe4(this, 0) && this->unk_24 == 0) {
        return 1;
    }
    return 0;
}
