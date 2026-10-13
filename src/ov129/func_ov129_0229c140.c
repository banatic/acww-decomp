/* func_ov129_0229c140 @ 0x0229c140, 0x30 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229c1d4(void *self);

struct UnkStruct_0229c140 {
    char pad_00[0xb4];
    unsigned char counter;
};

void func_ov129_0229c140(struct UnkStruct_0229c140 *self)
{
    if (self->counter != 0) {
        self->counter--;
        if (self->counter == 0) {
            func_ov129_0229c1d4(self);
        }
    }
}
