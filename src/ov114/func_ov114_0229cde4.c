/* func_ov114_0229cde4 @ 0x0229cde4, 0x34 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void *ptr);

void func_ov114_0229cde4(void *arg)
{
    int i;
    for (i = 0; i < 9; i++) {
        func_020b9ccc((char *) arg + 0x0e08 + i * 0x38);
    }
    ((char *) arg)[0x12b4] = 0;
}
