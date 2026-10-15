/* func_02083544 @ 0x02083544, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020835a0(void);

typedef struct {
    int unk_00;
    unsigned int unk_04;
} UnkStruct_02083544;

char *func_02083544(UnkStruct_02083544 *a, unsigned int b)
{
    char *result = 0;
    if (b < a->unk_04) {
        char *temp;
        temp = func_020835a0() + 8 + b * 8;
        result = temp + 4;
    }
    return result;
}
