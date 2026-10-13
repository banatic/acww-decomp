/* func_02059cf8 @ 0x02059cf8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[12];
    unsigned short unk_0C;
} UnkStruct_02059cf8;

extern int func_02059d28(UnkStruct_02059cf8 *obj);
extern char *data_020dd31c[];

char *func_02059cf8(UnkStruct_02059cf8 *obj, int size)
{
    if (obj->unk_0C == 9) {
        return data_020dd31c[3] + size * 24;
    } else {
        return data_020dd31c[func_02059d28(obj)] + size * 24;
    }
}
