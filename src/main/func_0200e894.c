/* func_0200e894 @ 0x0200e894, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long long a;
    long long b;
} LL2;
extern char *func_0200e86c(char *base, int index);

int func_0200e894(char *self, char *src)
{
    int count = *(int *) (self + 0xc7c);
    if (count < 30) {
        if (*(int *) (self + 0xc80) >= 0) {
            int sv = *(int *) (src + 4);
            if (*(int *) (func_0200e86c(self, *(int *) (self + 0xc80)) + 4) < sv) {
                *(int *) (self + 0xc80) = *(int *) (self + 0xc7c);
            }
        } else {
            *(int *) (self + 0xc80) = count;
        }
        {
            char *dst = self + 0x934 + 28 * *(int *) (self + 0xc7c);
            *(int *) dst = *(int *) src;
            *(int *) (dst + 4) = *(int *) (src + 4);
            *(short *) (dst + 8) = *(short *) (src + 8);
            {
                LL2 *s = (LL2 *) (src + 0xc);
                LL2 *d = (LL2 *) (dst + 0xc);
                *d = *s;
            }
            (*(int *) (self + 0xc7c))++;
        }
        return 1;
    }
    return 0;
}
