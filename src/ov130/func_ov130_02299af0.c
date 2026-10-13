/* func_ov130_02299af0 @ 0x02299af0, 0x98 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x290];
    unsigned short arr[0x40];
} UnkStruct_02299af0;

extern void func_ov130_022999a8(void *p, int a);

void func_ov130_02299af0(UnkStruct_02299af0 *self, int x, int y, int z)
{
    unsigned short v;
    unsigned int r6;

    if (x != 0xb) {
        v = (unsigned short) (x * 4 + 0x84);
    } else {
        v = 0x176;
    }
    r6 = y + z * 32;
    self->arr[r6] = v | (self->arr[r6] & 0xFC00);
    self->arr[r6 + 1] = (unsigned short) (v + 1) | (self->arr[r6 + 1] & 0xFC00);
    v += 2;
    if (x == 0xb) {
        v = 0x176;
    }
    self->arr[r6 + 0x20] = v | (self->arr[r6 + 0x20] & 0xFC00);
    self->arr[r6 + 0x21] = (unsigned short) (v + 1) | (self->arr[r6 + 0x21] & 0xFC00);
    func_ov130_022999a8(self, 1);
}
