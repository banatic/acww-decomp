/* func_02078234 @ 0x02078234, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC3];
    unsigned char flag;
} UnkStruct_02078234;

int func_02078234(UnkStruct_02078234 *s)
{
    if (s->flag & 0x10) {
        return 1;
    }
    return 0;
}
