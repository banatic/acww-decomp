/* func_0203d7c4 @ 0x0203d7c4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5c];
} Entry;

extern Entry data_021c6ec4[];
extern int func_020a8bb8(Entry *entry, int arg);

int func_0203d7c4(int index, int arg)
{
    return func_020a8bb8(&data_021c6ec4[index], arg);
}
