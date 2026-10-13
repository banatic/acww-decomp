/* func_0208a2b8 @ 0x0208a2b8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);

void func_0208a2b8(void *param)
{
    if (*(int *) ((char *) param + 0x34) != 0) {
        func_0208a0c8((char *) param + 0xc);
        func_0208a0c8((char *) param + 0x20);
    }
}
