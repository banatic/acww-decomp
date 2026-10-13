/* func_02039474 @ 0x02039474, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2e4];
    int arr[4];
} Matcher;

int func_02039474(Matcher *s, int value)
{
    int found = 0;
    int i;
    int v;

    for (i = found; i < 4; i++) {
        v = s->arr[i];
        if (v == value) {
            found = 1;
            break;
        }
    }
    return found;
}
