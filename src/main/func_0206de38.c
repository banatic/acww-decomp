/* func_0206de38 @ 0x0206de38, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x308];
    int arr[5];
    int count;
} UnkStruct_0206de38;

int func_0206de38(UnkStruct_0206de38 *self, int value)
{
    int i = 0;
    int n = self->count;
    while (i < n) {
        if (value < self->arr[i + 1]) {
            return i;
        }
        i++;
    }
    if (n < 4) {
        return n;
    }
    return 3;
}
