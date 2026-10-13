/* func_0206e83c @ 0x0206e83c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(void);

void func_0206e83c(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x10) != 0) {
        func_020e9898();
        *(unsigned int *) ((char *) arg0 + 0x10) = 0;
    }
}
