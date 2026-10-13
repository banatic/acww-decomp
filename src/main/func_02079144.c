/* func_02079144 @ 0x02079144, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02079350(void);

void func_02079144(void)
{
    int *ptr;
    int value;

    ptr = (int *) func_02079350();
    value = 0;
    ptr[0x5A] = value;
}
