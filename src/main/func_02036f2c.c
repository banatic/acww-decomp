/* func_02036f2c @ 0x02036f2c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned short arr[5];
    unsigned char bytes[4];
} UnkStruct_02036f2c;

void func_02036f2c(UnkStruct_02036f2c *p)
{
    p->arr[0] = 0xFFFF;
    p->arr[1] = 0xFFFF;
    p->arr[2] = 0xFFFF;
    p->arr[3] = 0xFFFF;
    p->arr[4] = 0xFFFF;
    p->bytes[0] = 0;
    p->bytes[1] = 0;
    p->bytes[2] = 0;
    p->bytes[3] = 0;
}
