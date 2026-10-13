/* func_ov048_022632f0 @ 0x022632f0, 0x10 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xe71];
    unsigned char byte;
} FnOv048Struct;

int func_ov048_022632f0(FnOv048Struct *p)
{
    p->byte = 0;
    return 1;
}
