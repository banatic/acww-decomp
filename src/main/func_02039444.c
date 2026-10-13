/* func_02039444 @ 0x02039444, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02039444 {
    char pad_00[0x2f4];
    int arr[4];
};

int func_02039444(struct UnkStruct_02039444 *s, int key)
{
    int result;
    int i;
    int v;

    result = 0;
    for (i = result; i < 4; i++) {
        v = s->arr[i];
        if (v == key) {
            result = 1;
            break;
        }
    }
    return result;
}
