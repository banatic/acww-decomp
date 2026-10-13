/* func_0208dd00 @ 0x0208dd00, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208dd00(void *ptr);

int func_0208dd00(void *ptr)
{
    if (*(int *) ((char *) ptr + 0x20) == 0) {
        return 1;
    }
    return 0;
}
