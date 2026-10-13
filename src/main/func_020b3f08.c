/* func_020b3f08 @ 0x020b3f08, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3f2c(char *p);

int func_020b3f08(char *p)
{
    char *ptr = p + 4 * func_020b3f2c(p);
    int i = 0;
    while (*ptr == 'F') {
        ptr += 4;
        i++;
    }
    return i;
}
