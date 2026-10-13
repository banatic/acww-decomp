/* func_ov003_02234cf0 @ 0x02234cf0, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern short func_0200322c(void *a, void *b);
extern int func_020a7278(void);

void func_ov003_02234cf0(char *self, const int *v)
{
    int c = *(unsigned char *) (self + 0x254);
    if (func_020a7278()) {
        if (v[0] != 0 && *(unsigned char *) (self + 0x24a) == 0 && c >= *(unsigned char *) (self + 0x255)) {
            *(short *) (self + 0x240) = func_0200322c((void *) v, self + 0x204);
            *(char *) (self + 0x251) = 7;
            *(char *) (self + 0x24a) = 1;
        }
    } else {
        if (*(unsigned char *) (self + 0x24a) == 0 && c >= *(unsigned char *) (self + 0x255)) {
            *(char *) (self + 0x24a) = 1;
            *(char *) (self + 0x251) = 7;
        }
    }
}
