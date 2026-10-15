/* func_0208fe1c @ 0x0208fe1c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e340(void);

int func_0208fe1c(void *object)
{
    int r4;
    int r0;

    r4 = 0;
    r0 = func_0203e340();
    if (r0 != 0) {
        r4 = 1;
    }
    r0 = r4;
    return r0;
}
