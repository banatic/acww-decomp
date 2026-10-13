/* func_020aad3c @ 0x020aad3c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7e50(void *arg);

int func_020aad3c(void *arg)
{
    return (func_020a7e50(arg) != 0) || (*(unsigned char *) ((char *) arg + 0x31) != 0);
}
