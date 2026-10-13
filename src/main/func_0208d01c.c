/* func_0208d01c @ 0x0208d01c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208d12c(void *);

int func_0208d01c(void *p)
{
    return (func_0208d12c(p) != 0) && (((int *) ((char *) p + 0xC8))[0] <= 0);
}
