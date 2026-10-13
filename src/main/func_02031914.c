/* func_02031914 @ 0x02031914, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short value;
    char pad_02[28];
} UnkStruct_02031914;
extern UnkStruct_02031914 data_020c907e[];
unsigned short func_02031914(int i)
{
    if (i < 0x7c) {
        return data_020c907e[i].value;
    } else {
        return 0xffff;
    }
}
