/* func_020a5b98 @ 0x020a5b98, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a5b98 {
    char pad_00[0xa8];
    int arr[4];
};

void func_020a5b98(struct UnkStruct_020a5b98 *s)
{
    int i = 3;
    do {
        s->arr[i] = 6;
        i--;
    } while (i >= 0);
}
