/* func_02014ba0 @ 0x02014ba0, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa5];
    unsigned char flag;
} UnkStruct_02014ba0;

extern int func_0201596c(UnkStruct_02014ba0 *ptr, int value);

int func_02014ba0(UnkStruct_02014ba0 *ptr)
{
    if (func_0201596c(ptr, 10)) {
        ptr->flag = 1;
        return 1;
    }
    return 0;
}
