/* func_0202cdf8 @ 0x0202cdf8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202cdf8 {
    int unk_00;
    int unk_04;
};

extern int func_0202ceac(int a, struct UnkStruct_0202cdf8 *p);

int func_0202cdf8(int a, struct UnkStruct_0202cdf8 **b)
{
    struct UnkStruct_0202cdf8 *arr;
    int sum;
    arr = *b;
    sum = 0;
    if (arr != 0) {
        int i;
        i = 0;
        do {
            sum += func_0202ceac(a, &arr[i]);
            i++;
        } while (i < 2);
    }
    return sum;
}
