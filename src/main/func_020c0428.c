/* func_020c0428 @ 0x020c0428, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a160(void *ptr);

void func_020c0428(void *arg)
{
    int result;
    void *ptr = arg;

    result = func_0208a160((char *) ptr + 0x10);
    if (result != 0) {
        *(int *) ((char *) ptr + 4) = 3;
    }
}
