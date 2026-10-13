/* func_02081988 @ 0x02081988, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7C];
    unsigned short : 7;
    unsigned short flag : 1;
} UnkStruct_02081988;

int func_02081988(UnkStruct_02081988 *p)
{
    if (p->flag) {
        return 1;
    } else {
        return 0;
    }
}
