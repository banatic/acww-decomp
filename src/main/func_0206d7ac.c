/* func_0206d7ac @ 0x0206d7ac, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern void func_02051c08(const void *src, void *dst, int size);
extern int func_02051c8c_unk(const void *ptr, int size);
extern int func_0206d780(u16 value);
extern int func_0206d714(u16 *ptr, int size);
extern u8 data_021ce2f8[0xfa];

int func_0206d7ac(char *arg0)
{
    int flag;
    int result;
    u16 *p;
    u16 buffer[0x40];
    int i;
    int j;
    int count1;
    int count2;
    int n;

    func_02051c08(arg0 + 0x58, buffer, 0x40);
    count1 = 0;
    count2 = count1;
    n = func_02051c8c_unk(buffer, 0x40);
    j = 0;
    i = j;
    do {
        data_021ce2f8[j] = i;
        j++;
    } while (j < 0xfa);

    flag = 1;
    while (i < n) {
        p = &buffer[i];
        result = func_0206d780(buffer[i]);
        if (flag == 1 && result == 0) {
            count1++;
            if (func_0206d714(p, n - i) != 0) {
                count2++;
            }
        }
        flag = result;
        i++;
    }

    if (count1 >= 3 && ((count1 + 3) >> 2) <= count2) {
        return 2;
    }
    if (count1 >= 2) {
        return 1;
    }
    return 0;
}
