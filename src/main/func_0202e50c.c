/* func_0202e50c @ 0x0202e50c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void);
extern int func_020036c0(void);

int func_0202e50c(void *arg0)
{
    int result = 2;
    if (*(unsigned int *) ((char *) arg0 + 0x830) != 0) {
        func_0208150c();
        result = func_020036c0();
    }
    return result;
}
