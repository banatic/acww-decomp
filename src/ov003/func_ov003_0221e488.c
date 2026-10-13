/* func_ov003_0221e488 @ 0x0221e488, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221e580(void *self, int arg2);

typedef struct {
    unsigned char pad_00[0x134];
    unsigned char state;
} UnkStruct_0221e488;

void func_ov003_0221e488(UnkStruct_0221e488 *self)
{
    if (self->state == 4) {
        func_ov003_0221e580(self, 2);
    }
}
