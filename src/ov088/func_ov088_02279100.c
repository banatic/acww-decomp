/* func_ov088_02279100 @ 0x02279100, 0x3c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov088_0227913c(int a, const unsigned char *str, int limit);
extern int func_020644cc(int x);

int func_ov088_02279100(int a, const unsigned char *str, int limit)
{
    int count;
    int index;
    int result;

    count = func_ov088_0227913c(a, str, limit);
    result = 0;
    if (count <= 0) {
        return -1;
    }

    count = func_020644cc(count);
    index = 0;

    while (index <= limit) {
        if (*str == 0) {
            if (count == 0) {
                result = index;
                break;
            }
            count--;
        }
        str++;
        index++;
    }

    return result;
}
