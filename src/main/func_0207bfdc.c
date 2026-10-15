/* func_0207bfdc @ 0x0207bfdc, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207b3dc(char *);
extern unsigned int func_0208150c(char *);
extern int func_02003704(void *);
extern int func_0207dca8(char *);
extern int func_0207cc54(unsigned char, int, int);
int func_0207bfdc(char *param)
{
    char *ptr = param;
    int result = func_0207b3dc(param);
    unsigned char flags = 0;
    int count = 0;
    int i;
    for (i = 0; i < 8; ptr += 0x7ec, i++) {
        if ((i == ((signed char *) param)[0x4075]) || (i == result)) {
            continue;
        }
        if (func_02003704((void *) func_0208150c(ptr)) == 0) {
            continue;
        }
        if (func_0207dca8(ptr) == 0) {
            continue;
        }
        flags |= 1 << i;
        count++;
    }

    return func_0207cc54(flags, count, 8);
}
