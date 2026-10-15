/* func_ov009_022655c4 @ 0x022655c4, 0x10 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_022655d4(void *state);

typedef struct {
    char pad_00[0x24];
    void (*handler)(void *);
    char pad_28[0x92 - 0x28];
    unsigned char byte;
} UnkStruct_022655c4;

void func_ov009_022655c4(UnkStruct_022655c4 *obj)
{
    obj->handler = func_ov009_022655d4;
    obj->byte = 2;
}
