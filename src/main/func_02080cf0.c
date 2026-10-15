/* func_02080cf0 @ 0x02080cf0, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080d0c(void *);

int func_02080cf0(void *argument0)
{
    int r0;
    int r2;
    int r1;

    r0 = func_02080d0c((void *) argument0);
    r2 = 0;
    r1 = ~r2;
    if (r0 != r1) {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}
