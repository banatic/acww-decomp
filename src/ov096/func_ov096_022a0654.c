/* func_ov096_022a0654 @ 0x022a0654, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb5];
    unsigned char b5;
    unsigned char pad_B6[0x244a];
    unsigned char data[1];
} UnkStruct_022a0654;

extern int func_0208e484(void *ptr);
extern int func_ov096_022a18dc(UnkStruct_022a0654 *self, int arg);
extern void func_ov096_0229dbe8(UnkStruct_022a0654 *self);

void func_ov096_022a0654(UnkStruct_022a0654 *self)
{
    if (func_0208e484(&self->data[0]) != 0) {
        if (func_ov096_022a18dc(self, self->b5 - 0x19) == 0) {
            func_ov096_0229dbe8(self);
        }
    }
}
