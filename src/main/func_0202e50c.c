/* func_0202e50c @ 0x0202e50c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int object);
extern int func_020036c0(unsigned char *);

int func_0202e50c(void *arg0)
{
    int result = 2;
    if (*(unsigned int *) ((char *) arg0 + 0x830) != 0) {
        result = func_020036c0((unsigned char *) func_0208150c(*(unsigned int *) ((char *) arg0 + 0x830)));
    }
    return result;
}
