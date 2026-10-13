/* func_0203d4f8 @ 0x0203d4f8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x20];
    unsigned int index;
} UnkStruct_0203d4f8;

extern unsigned int data_020ca4a0[];

unsigned int func_0203d4f8(UnkStruct_0203d4f8 *obj)
{
    return data_020ca4a0[obj->index];
}
