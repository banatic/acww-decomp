/* func_ov103_0229c8e8 @ 0x0229c8e8, 0x28 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov103_0229cd1c(void *self, int arg1, char *data);

typedef struct {
    char pad_00[0x2ba0];
    char data[0x200];
    unsigned char flag;
} UnkStruct_0229c8e8;

void func_ov103_0229c8e8(UnkStruct_0229c8e8 *self, int arg1)
{
    if (self->flag == 1) {
        func_ov103_0229cd1c(self, arg1, self->data);
    }
    self->flag = 0;
}
