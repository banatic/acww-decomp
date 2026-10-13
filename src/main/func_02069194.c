/* func_02069194 @ 0x02069194, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8754(void *ptr);

void func_02069194(void *ptr)
{
    *(unsigned int *) ((char *) ptr + 0x28) = 0;
    func_020a8754((char *) ptr + 0x2c);
}
