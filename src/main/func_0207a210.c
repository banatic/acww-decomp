/* func_0207a210 @ 0x0207a210, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int x);

typedef struct {
    char pad_00[8];
    signed char arr[4];
} UnkStruct_0207a210;

int func_0207a210(UnkStruct_0207a210 *s, int b)
{
    int i;
    if (func_0207cf74(b) == 0) {
        goto fail;
    }
    for (i = 0; i < 4; i++) {
        if (b == s->arr[i]) {
            return i;
        }
    }
fail:
    return -1;
}
