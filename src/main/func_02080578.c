/* func_02080578 @ 0x02080578, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02095040(void *);
extern int func_0209871c(void *, void *);
extern int memcmp(const void *, const void *, unsigned int);

int func_02080578(unsigned short *a, unsigned short *b, void *c)
{
    int flag = 0;
    unsigned short *p = func_02095040((void *) a);
    if (*b == *p) {
        if (memcmp((char *) b + 2, (char *) p + 2, 12) == 0) {
            if (func_0209871c(c, a) == ~flag) {
                flag = 1;
            }
        }
    }
    return flag;
}
