/* func_ov117_02299c50 @ 0x02299c50, 0x18 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

void func_ov117_02299c50(unsigned char *arr)
{
    unsigned int i;
    unsigned char fill;
    i = 0;
    fill = i;
    goto test;
loop:
    arr[i] = fill;
    i++;
test:
    if (i < 0x200) {
        goto loop;
    }
}
