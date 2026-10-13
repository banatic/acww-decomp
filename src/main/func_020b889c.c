/* func_020b889c @ 0x020b889c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xFC];
    unsigned int index;
    char pad_100[8];
    int value;
    char flag;
} UnkStruct_020b889c;

extern short data_020d2298[];

void func_020b889c(UnkStruct_020b889c *ptr)
{
    ptr->value = data_020d2298[ptr->index];
    ptr->flag = 1;
}
