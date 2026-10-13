/* func_02001d74 @ 0x02001d74, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02001d44(int);

typedef struct {
    char pad_00[12];
    char unk_0C;
} UnkStruct_02001d74;

extern UnkStruct_02001d74 data_0213fe94;

int func_02001d74(char a, int b)
{
    data_0213fe94.unk_0C = a;
    return func_02001d44(b);
}
