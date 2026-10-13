/* func_ov145_0229a15c @ 0x0229a15c, 0x28 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *);
extern void func_ov002_0220a580(void *);

int func_ov145_0229a15c(void *arg0)
{
    if (func_0208e930((char *) arg0 + 0x12c)) {
        func_ov002_0220a580((char *) arg0 + 0x12c);
        return 1;
    }
    return 0;
}
