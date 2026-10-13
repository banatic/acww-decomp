/* func_0208e5d4 @ 0x0208e5d4, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);

void func_0208e5d4(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x40) != 0) {
        func_0208a0c8((char *) arg0 + 0xc);
        if (*(unsigned char *) ((char *) arg0 + 0x49) != 0) {
            func_0208a0c8((char *) arg0 + 0x2c);
        }
    }
}
