/* func_ov112_0229f630 @ 0x0229f630, 0x38 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f630 {
    char pad_00[0x94];
    int count;
    char pad_98[0x6bb8];
    int arr[1];
};

int func_ov112_0229f630(struct UnkStruct_0229f630 *p, int val)
{
    int i = 0;
    int n = p->count;
    while (i < n) {
        if (val < p->arr[i + 1]) {
            return i;
        }
        i++;
    }
    if (n < 6) {
        return n;
    }
    return 5;
}
