/* func_ov003_02223c58 @ 0x02223c58, 0x22 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02224138(void *p);
struct UnkStruct_02223c58 {
    char pad_00[0x40];
    int unk_40;
};
void func_ov003_02223c58(struct UnkStruct_02223c58 *self)
{
    char *p = (char *) self;
    int i;
    for (i = 0; i < 2; i++) {
        func_ov003_02224138(p);
        p += 0x20;
    }
    self->unk_40 = -1;
}
