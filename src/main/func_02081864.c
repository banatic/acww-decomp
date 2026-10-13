/* func_02081864 @ 0x02081864, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short : 5;
    unsigned short target : 1;
} UnkStruct_02081864;

int func_02081864(UnkStruct_02081864 *arg)
{
    return arg->target ? 1 : 0;
}
