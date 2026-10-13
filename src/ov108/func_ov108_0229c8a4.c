/* func_ov108_0229c8a4 @ 0x0229c8a4, 0x24 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xac];
    char unk_AC;
    char pad_AD[0x1ff];
    unsigned char unk_2AC;
} UnkStruct_0229c8a4;

extern void func_ov108_0229cc90(UnkStruct_0229c8a4 *self, void *other, char *addr);

void func_ov108_0229c8a4(UnkStruct_0229c8a4 *self, void *other)
{
    if (self->unk_2AC == 1) {
        func_ov108_0229cc90(self, other, &self->unk_AC);
    }
    self->unk_2AC = 0;
}
