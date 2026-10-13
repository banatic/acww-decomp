/* func_0208a4dc @ 0x0208a4dc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void);

void func_0208a4dc(void *arg0)
{
    if (*(int *) ((char *) arg0 + 0xc0) != 0) {
        func_020a8fb8();
        *(int *) ((char *) arg0 + 0xc0) = 0;
    }
    if (*(int *) ((char *) arg0 + 0xc4) != 0) {
        func_020a8fb8();
        *(int *) ((char *) arg0 + 0xc4) = 0;
    }
}
