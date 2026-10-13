/* func_ov116_0229ddb8 @ 0x0229ddb8, 0x18 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1428];
    unsigned short unk_1428;
} StructAtOffset1428;

int func_ov116_0229ddb8(StructAtOffset1428 *obj, unsigned short mask)
{
    if ((obj->unk_1428 & mask) == 0) {
        return 0;
    } else {
        return 1;
    }
}
