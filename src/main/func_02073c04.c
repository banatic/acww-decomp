/* func_02073c04 @ 0x02073c04, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073918(void *self, int a);

struct UnkStruct_02073c04 {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x64 - 0x24 - 4];
    int unk_64;
};

int func_02073c04(struct UnkStruct_02073c04 *self, int param1, int param2)
{
    if (param1 >= 4) {
        return self->unk_24;
    }
    if (func_02073918(self, param1) != 0) {
        return 0;
    }
    if (param1 < self->unk_64) {
        return self->unk_24 + ((param2 + param1 * 3) << 12);
    } else {
        return self->unk_24 + ((param2 + (param1 - 1) * 3) << 12);
    }
}
