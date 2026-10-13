/* func_02034e78 @ 0x02034e78, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02037470(void *a, void *b);

void func_02034e78(void *self, int start)
{
    int count;
    int i;
    int *p;

    count = *(int *) ((char *) self + 0x1c0);
    if (count > 0) {
        i = count - 1;
        while (i >= start) {
            func_02037470((char *) self + 0x1c * (i + 1), (char *) self + 0x1c * i);
            i--;
        }
    }
    p = (int *) ((char *) self + 0x1c0);
    (*p)++;
}
