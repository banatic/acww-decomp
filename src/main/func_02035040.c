/* func_02035040 @ 0x02035040, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02037470(void *a, void *b);
extern void func_020374ac(void *a);

void func_02035040(void *self)
{
    int i, j;
    int count;
    int last;

    count = *(int *) ((char *) self + 0x1c0);
    for (i = count - 1; i >= 0; i--) {
        if (*(unsigned char *) ((char *) self + i * 0x1c + 0x13) != 0) {
            last = *(int *) ((char *) self + 0x1c0) - 1;
            for (j = i; j < last; j++) {
                func_02037470((char *) self + j * 0x1c, (char *) self + (j + 1) * 0x1c);
            }
            func_020374ac((char *) self + last * 0x1c);
            *(int *) ((char *) self + 0x1c0) = last;
        }
    }
}
