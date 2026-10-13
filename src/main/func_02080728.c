/* func_02080728 @ 0x02080728, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d60(void *);
extern int func_0209518c(int, int);

int func_02080728(void *arr, int val)
{
    int i = 0;
    while (i < 8) {
        if (func_0209518c(func_02081d60((char *) arr + (i << 7)), val)) {
            return i;
        }
        i++;
    }
    return -1;
}
