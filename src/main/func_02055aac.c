/* func_02055aac @ 0x02055aac, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ec4(void *p);
extern void func_020e993c(void *p, int q);

void func_02055aac(void *self)
{
    if (*(int *) ((char *) self + 4) != 0) {
        func_020e993c(*(void **) ((char *) self + 8), *(int *) ((char *) self + 4));
    }
    *(int *) ((char *) self + 4) = 0;
    *(int *) ((char *) self + 8) = 0;
    *(int *) ((char *) self + 0xc) = 0;
    *(int *) ((char *) self + 0x10) = 0;
    *(char *) ((char *) self + 0x30) = 0;
    func_020b9ec4((char *) self + 0x14);
}