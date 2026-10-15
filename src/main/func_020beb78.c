/* func_020beb78 @ 0x020beb78, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020be9f8(void);
extern int func_ov003_022197c4(int, int);

void func_020beb78(int param1, int param2)
{
    int *ptr;
    int local;

    ptr = (int *) param1;
    *(unsigned char *) (param1 + 0x21) = (unsigned char) param2;
    *ptr = 2;
    local = 1;
    func_ov003_022197c4(local, *(ptr + 1));
    func_020be9f8();
}
