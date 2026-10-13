/* func_0201c9a4 @ 0x0201c9a4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(int a, int b);
extern int data_020c8ed4[5];

int func_0201c9a4(int a, int b)
{
    int result = func_020164a0(b + 0x334, 0);
    int *p = data_020c8ed4;
    int i = 0;
    for (; i < 5; p++, i++) {
        if (result == *p) {
            return 1;
        }
    }
    return 0;
}
