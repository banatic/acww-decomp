/* func_ov113_0229a148 @ 0x0229a148, 0x4c bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov113_02299aa4(void *);
extern void func_ov113_02299980(void *);
extern void func_ov113_022998cc(void *);
extern void func_ov002_0220a164(void *);

void func_ov113_0229a148(void *arg)
{
    char *p = (char *) arg;
    if (func_0208e484(p + 0x2b20) != 0) {
        if (func_ov113_02299aa4(p) != 0) {
            if ((unsigned char) (*(unsigned char *) (p + 0x9b) + 0xfe) <= 1) {
                func_ov113_02299980(p);
            } else {
                func_ov002_0220a164(p + 0x2b20);
            }
        } else {
            func_ov113_022998cc(p);
        }
    }
}
