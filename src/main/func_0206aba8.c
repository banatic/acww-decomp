/* func_0206aba8 @ 0x0206aba8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8750(void *ptr);

void func_0206aba8(void *arg)
{
    void *ptr = (char *) arg + 0x38;
    func_020a8750(ptr);
    *(unsigned int *) ((char *) arg + 0x30) = 4;
}
