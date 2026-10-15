/* func_02067fd4 @ 0x02067fd4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02067fd4 {
    unsigned char pad_00[0x1a6b];
    unsigned char byte;
    unsigned char pad_1A6C[0x1bb0 - 0x1a6b - 1];
    unsigned char data[1];
} UnkStruct_02067fd4;

extern int func_020b45d0(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned char *func_02067fd4(UnkStruct_02067fd4 *self)
{
    unsigned int b = self->byte;
    if (b >= 12) {
        b -= 12;
    }
    if (b == 0) {
        b = 12;
    }
    func_020b45d0(self->data, b, 2, 0, 0, 0);
    return self->data;
}
