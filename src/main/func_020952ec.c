/* func_020952ec @ 0x020952ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);

int func_020952ec(void)
{
    int *ptr;
    int result;

    ptr = (int *) func_02096718(4);
    result = ptr[0x200];
    return result;
}
