/* func_ov055_022609f4 @ 0x022609f4, 0x10 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov055_02260e60;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} Struct_ov055_022609f4;

int func_ov055_022609f4(int unused, Struct_ov055_022609f4 *out)
{
    out->unk_00 = data_ov055_02260e60;
    out->unk_04 = 0x38;
    return 0x38;
}
