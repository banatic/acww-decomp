/* func_020ab17c @ 0x020ab17c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[8];
    int arr[5];
} UnkStruct_020ab17c;

extern void func_02051694(int arg);

void func_020ab17c(UnkStruct_020ab17c *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->arr[i] != 0) {
            func_02051694(s->arr[i]);
        }
    }
}
