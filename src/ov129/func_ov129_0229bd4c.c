/* func_ov129_0229bd4c @ 0x0229bd4c, 0xb8 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299a18(const void *p, const void *a, const void *b, unsigned int *out1, unsigned int *out2);
extern unsigned int func_ov127_02299844(unsigned int a, unsigned int b);
extern unsigned int func_ov127_02299804(unsigned int a, unsigned int b);
extern const int data_ov129_0229db04[5];
extern const int data_ov129_0229db18[5];

typedef struct {
    unsigned char pad_00[0xaa];
    unsigned short hword;
    unsigned char pad_AC[4];
    unsigned char byte;
} UnkStruct_0229bd4c;

int func_ov129_0229bd4c(UnkStruct_0229bd4c *self, const char *a, const char *b)
{
    unsigned int zero1 = 0;
    unsigned int zero2 = 0;
    unsigned int out1, out2;
    int i;

    self->byte = 0xff;
    self->hword = 0xffff;

    for (i = 0; i < 5; i++) {
        if (func_ov127_02299a18((const char *) self + 0x734, a + data_ov129_0229db04[i], b + data_ov129_0229db18[i], &out1,
                                &out2) != 0) {
            if (self->byte == 0xff) {
                unsigned int val = func_ov127_02299844(out1, out2);
                if (val != ~zero1) {
                    self->byte = (unsigned char) val;
                }
            }
            if (self->hword == 0xffff) {
                unsigned int val = func_ov127_02299804(out1, out2);
                if (val != ~zero2) {
                    self->hword = (unsigned short) val;
                }
            }
        }
    }

    if (self->byte != 0xff || self->hword != 0xffff) {
        return 1;
    }
    return 0;
}