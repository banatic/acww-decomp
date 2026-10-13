/* func_02073928 @ 0x02073928, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int n);

struct UnkStruct_02073928 {
    char pad_00[0x4c];
    unsigned int arr1[3];
    unsigned int arr2[1];
};

int func_02073928(struct UnkStruct_02073928 *s, int n)
{
    int idx = func_02077b58(n);
    unsigned int a = s->arr2[idx];
    if (a >= 3) {
        return s->arr1[idx];
    } else {
        unsigned int sum = a + s->arr1[idx];
        if (sum >= 3) {
            sum -= 3;
        }
        return sum;
    }
}
