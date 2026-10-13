/* func_0209a69c @ 0x0209a69c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(void *p);
extern int memcmp(void *dst, void *src, unsigned int n);
extern int func_0209518c(void *a, void *b);

int func_0209a69c(char *a, char *b)
{
    char *p;
    int i;

    if (func_020951bc(b) != 0) {
        p = a + 0x1c;
        for (i = 0; i < 5; i++) {
            if (*(unsigned short *) b == *(unsigned short *) p && memcmp(b + 2, p + 2, 12) == 0 && func_0209518c(b, p) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
