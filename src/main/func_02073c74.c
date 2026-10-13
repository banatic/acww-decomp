/* func_02073c74 @ 0x02073c74, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int x);

typedef struct {
    char pad_00[0x18];
    int array[1];
} UnkStruct_02073c74;

void func_02073c74(UnkStruct_02073c74 *s, int key, int value)
{
    s->array[func_02077b58(key)] = value;
}
