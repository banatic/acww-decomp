/* func_ov009_02264328 @ 0x02264328, 0x48 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264264(void *self, int b, int d, void *c);

void func_ov009_02264328(void *self, int b, void *c, int d)
{
    if (func_ov009_02264264(self, b, d, c)) {
        *(unsigned char *) ((unsigned char *) *(unsigned char **) ((char *) self + 0x4c) + 0x235) |= 2;
        if (*(int *) ((char *) c + 0x98) >= 0x200) {
            *(unsigned char *) ((unsigned char *) *(unsigned char **) ((char *) self + 0x4c) + 0x235) |= 4;
        }
    }
}
