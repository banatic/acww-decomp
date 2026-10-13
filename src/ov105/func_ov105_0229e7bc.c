/* func_ov105_0229e7bc @ 0x0229e7bc, 0x48 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int AOSS_FD_SET(void *p);
extern void func_ov002_02208098(void *p, int i);
extern void func_ov105_0229cadc(void *p, int i, int j);

typedef struct {
    unsigned char pad_00[0x2b5];
    unsigned char byte_at_2b5;
    unsigned char pad_2B6[0x0d];
    unsigned char byte_at_2c3;
    unsigned char pad_2C4[0x20f8];
    unsigned char arr[1];
} UnkStruct_0229e7bc;

void func_ov105_0229e7bc(UnkStruct_0229e7bc *self)
{
    if (AOSS_FD_SET(self->arr)) {
        if (self->byte_at_2c3 != 0) {
            self->byte_at_2c3--;
        } else {
            func_ov105_0229cadc(self, self->byte_at_2b5, 1);
            func_ov002_02208098(self, 2);
        }
    }
}
