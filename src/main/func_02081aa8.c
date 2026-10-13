/* func_02081aa8 @ 0x02081aa8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short : 2;
    unsigned short bit2 : 1;
} UnkStruct_02081aa8;

int func_02081aa8(UnkStruct_02081aa8 *s)
{
    return (s->bit2 == 1) ? 1 : 0;
}
