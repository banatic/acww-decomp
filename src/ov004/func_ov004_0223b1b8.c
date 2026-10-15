/* func_ov004_0223b1b8 @ 0x0223b1b8, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223b1c8(void *);

typedef struct {
    char pad_00[0x24];
    void (*handler)(void *);
    char pad_28[0x92 - 0x28];
    unsigned char byte;
} UnkStruct_0223b1b8;

void func_ov004_0223b1b8(UnkStruct_0223b1b8 *obj)
{
    obj->handler = func_ov004_0223b1c8;
    obj->byte = 2;
}
