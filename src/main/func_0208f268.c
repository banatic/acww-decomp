/* func_0208f268 @ 0x0208f268, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);

void func_0208f268(void *param)
{
    if (*(unsigned int *) ((char *) param + 0x44) != 0) {
        func_0208a0c8((char *) param + 0x1c);
        func_0208a0c8((char *) param + 0x30);
    }
}
