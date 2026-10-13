/* func_ov048_02260714 @ 0x02260714, 0x3c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0201c014(void *);

struct UnkStruct_02260714 {
    unsigned char pad_00[0x563];
    unsigned char unk_563;
    unsigned char pad_564[0xb4];
    unsigned char unk_618;
};

int func_ov048_02260714(struct UnkStruct_02260714 *self)
{
    if (self->unk_563) {
        return 1;
    }
    if (func_02014868(&self->unk_618) != 0) {
        goto ret0;
    }
    if (func_0201c014(self) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
