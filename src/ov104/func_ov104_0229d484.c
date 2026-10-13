/* func_ov104_0229d484 @ 0x0229d484, 0x22 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xB4];
    unsigned char flag;
    char pad_B5[0x0B];
    char sub;
} UnkStruct_0229d484;

extern void func_ov104_0229d938(void *a, int b, void *c);

void func_ov104_0229d484(UnkStruct_0229d484 *self, int a)
{
    if (self->flag == 1) {
        func_ov104_0229d938(self, a, &self->sub);
    }
    self->flag = 0;
}
