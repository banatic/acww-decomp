/* text_string_5: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051d30 @ 0x02051d30, 0x10 bytes, Thumb
 * func_02051d08 @ 0x02051d08, 0x28 bytes, Thumb
 * func_02051ce0 @ 0x02051ce0, 0x28 bytes, Thumb
 * func_02051ca8 @ 0x02051ca8, 0x38 bytes, Thumb
 * func_02051c90 @ 0x02051c90, 0x16 bytes, Thumb
 */

int func_02051d30(int arg)
{
    if (arg == 10 || arg == 0) {
        return 0;
    } else {
        return 10;
    }
}

int func_02051d08(unsigned short *arr, int count)
{
    int sum = 0;
    int i;
    for (i = 0; i < count; i++) {
        sum += func_02051d30(arr[i]);
    }
    return sum;
}

int func_02051ce0(unsigned short *arr, int count, int offset)
{
    int i = 0;
    while (i < count) {
        unsigned short value = arr[i];
        if (value == 0) {
            return i;
        }
        if (value == 0xa) {
            return i + offset;
        }
        i++;
    }
    return i;
}

int func_02051ca8(unsigned short *arr, int n)
{
    int i;
    int result = 0;
    i = result;
    while (i < n) {
        if (arr[i] == 0) {
            return result;
        }
        if (arr[i] != 0x3000 && arr[i] != 0x20) {
            result = i + 1;
        }
        i++;
    }
    return result;
}

int func_02051c90(unsigned short *arr, int count, int arg2, int start)
{
    int i = start;
    do {
        if (arr[i] == 0) {
            return i;
        }
        i++;
    } while (i < count);
    return i;
}
