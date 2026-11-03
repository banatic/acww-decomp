/* scene_actor_7: 3 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_022638cc @ 0x022638cc, 0x4 bytes, Thumb
 * func_ov009_022638c8 @ 0x022638c8, 0x2 bytes, Thumb
 * func_ov009_02263888 @ 0x02263888, 0x40 bytes, Thumb
 */

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
    char pad_138[0xFE];
    unsigned char unk_236;
    unsigned char unk_237;
    char pad_238[0x48];
    unsigned char unk_280;
} UnkStruct_02263888;

extern void func_020b248c(unsigned short);

int func_ov009_022638cc(void *object)
{
    return 1;
}

void func_ov009_022638c8(void *object) {}

int func_ov009_02263888(UnkStruct_02263888 *self)
{
    if (self->unk_280 == 0) {
        func_020b248c(self->unk_136);
    }
    self->unk_236 &= ~2;
    self->unk_237 = 0;
    return 1;
}
