/* func_ov003_02223928 @ 0x02223928, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02222b78(char *p);
extern void func_ov003_022231e8(char *p);
void func_ov003_02223928(char *base)
{
    int i, j;
    func_ov003_02222b78(base + 0x1e4c);
    i = 0;
    do {
        j = 0;
        do {
            func_ov003_022231e8(base + i * 0x530 + j * 0x14c);
            j++;
        } while (j < 4);
        i++;
    } while (i < 3);
    i = 0;
    do {
        func_ov003_022231e8(base + 0xf90 + i * 0x14c);
        func_ov003_022231e8(base + 0x18a4 + i * 0x14c);
        i++;
    } while (i < 4);
}
