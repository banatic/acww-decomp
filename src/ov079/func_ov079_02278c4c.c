/* func_ov079_02278c4c @ 0x02278c4c, 0x30 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} UnkStruct_02278c4c;

extern unsigned char data_ov079_0227a1b0[];
extern int func_0202ea80(int a, int b);
extern int func_020644cc(int a);

void func_ov079_02278c4c(int unused, UnkStruct_02278c4c *self)
{
    self->unk_00 = (unsigned int) data_ov079_0227a1b0;
    if (func_0202ea80(10, 0) == 0) {
        self->unk_04 = 0;
    } else {
        self->unk_04 = (unsigned char) (func_020644cc(3) + 6);
    }
}
