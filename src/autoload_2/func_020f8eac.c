/* func_020f8eac @ 0x020f8eac, 0xd0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_020f8eac {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

extern int func_020f8e6c(struct UnkStruct_020f8eac *self, int idx, int value);
extern void func_020f7bc4(struct UnkStruct_020f8eac *self, int off, int *ptr);
extern void ciAddUNQUIETFilter(struct UnkStruct_020f8eac *self, int value);

void func_020f8eac(struct UnkStruct_020f8eac *self, int unused, int value)
{
    int idx4;
    int s;

    idx4 = self->unk_10 * 4;
    s = func_020f8e6c(self, self->unk_10, value);
    switch (s) {
        case 1:
            func_020f7bc4(self, idx4 + 0x507, &self->unk_04);
            break;
        case 2:
            func_020f7bc4(self, idx4 + 0x508, &self->unk_04);
            break;
        case 3:
            func_020f7bc4(self, idx4 + 0x509, &self->unk_04);
            break;
        case 4:
            func_020f7bc4(self, idx4 + 0x50a, &self->unk_04);
            self->unk_10 = (self->unk_10 + 1) % 2;
            break;
        default:
            break;
    }
    ciAddUNQUIETFilter(self, value);
}
