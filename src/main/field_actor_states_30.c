/* field_actor_states_30: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200e894 @ 0x0200e894, 0x78 bytes, Thumb
 * func_0200e86c @ 0x0200e86c, 0x28 bytes, Thumb
 * func_0200e854 @ 0x0200e854, 0x18 bytes, Thumb
 * func_0200e828 @ 0x0200e828, 0x2c bytes, Thumb
 */

typedef struct {
    long long a;
    long long b;
} LL2;

char *func_0200e86c(char *base, int index);

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

char *func_0200e86c(char *base, int index)
{
    if (index >= 0 && index < 30 && index < *(int *) (base + 0xc7c)) {
        return base + 0x934 + 28 * index;
    }
    return 0;
}

void func_0200e854(void *r0)
{
    unsigned int *base = (unsigned int *) r0;
    base[0x31f] = 0;
    base[0x320] = 0xffffffff;
}

int func_0200e828(void *arg)
{
    int index;
    int r2 = 0;
    int r0;

    if ((index = *(int *) ((char *) arg + 0xC80)) >= 0) {
        char *ret = (char *) func_0200e86c((char *) arg, index);
        r2 = *(int *) (ret + 4);
    }
    r0 = *(int *) ((char *) arg + 0x7FC);
    if (r0 <= r2) {
        r0 = r2;
    }
    return r0;
}
