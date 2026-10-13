/* func_02081cd8 @ 0x02081cd8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02081cd8 {
    unsigned char pad_00[0x7c];
    unsigned short flag : 1;
};

int func_02081cd8(struct UnkStruct_02081cd8 *s)
{
    return (s->flag == 1);
}
