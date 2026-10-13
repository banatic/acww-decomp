/* func_020731a4 @ 0x020731a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

typedef struct {
    unsigned char pad_00[0x128];
    unsigned short arr[64];
} UnkStruct_020731a4;

void func_020731a4(UnkStruct_020731a4 *s, int value)
{
    s->arr[func_02077b58(value)] = 0;
}
