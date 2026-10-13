/* func_ov090_02298f74 @ 0x02298f74, 0x10 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

struct Unk_2298f74 {
    unsigned char pad_00[0x98];
    unsigned char flag;
};

int func_ov090_02298f74(struct Unk_2298f74 *self)
{
    if (self->flag == 0) {
        return 0;
    }
    return 1;
}
