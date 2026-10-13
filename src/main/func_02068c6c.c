/* func_02068c6c @ 0x02068c6c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a234(void *ptr);
extern int func_0208a20c(void *ptr);

int func_02068c6c(void *param)
{
    if (*(unsigned int *) ((char *) param + 0x7c) == 0) {
        if (func_0208a234((char *) param + 0xc) == 2) {
            param = (char *) param + 0xc;
            if (func_0208a20c(param)) {
                return 1;
            }
        }
    }
    return 0;
}
