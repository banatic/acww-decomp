/* func_02048a54 @ 0x02048a54, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

int func_02048a54(void *unused, Pair *a, Pair *arr, int count)
{
    int result = 0;
    while (count != 0) {
        if (a->unk_00 == arr->unk_00 && a->unk_04 == arr->unk_04) {
            result = 1;
            break;
        }
        arr++;
        count--;
    }
    return result;
}
