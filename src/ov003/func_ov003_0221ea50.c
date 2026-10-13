/* func_ov003_0221ea50 @ 0x0221ea50, 0x12 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ad1f4(void *p);

struct UnkStruct_0221ea50 {
    char pad_00[0x5c];
    char member;
};

int func_ov003_0221ea50(struct UnkStruct_0221ea50 *self)
{
    func_020ad1f4(&self->member);
    return 1;
}
