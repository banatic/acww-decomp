/* func_ov003_02216fec @ 0x02216fec, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_ov003_02216c9c(void *, int);
extern int func_ov003_02216eb4(void *, int, int);

void func_ov003_02216fec(void *p)
{
    if (func_02056f94((char *) p + 0x2d0)) {
        if (!func_ov003_02216c9c(p, 1)) {
            func_ov003_02216eb4(p, 6, -1);
        }
    }
}
