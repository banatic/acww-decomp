/* func_020c1fb8 @ 0x020c1fb8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char func_020c1fb8(void *arg0);

char func_020c1fb8(void *arg0)
{
    char *ptr;
    char value;

    ptr = (char *) arg0;
    value = 0;
    ptr[0x728] = value;
    return 1;
}
