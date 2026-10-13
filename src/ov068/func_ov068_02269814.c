/* func_ov068_02269814 @ 0x02269814, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea9e4(void *, void *);

int func_ov068_02269814(void *a, void *b)
{
    if (func_020ea9e4((char *) b + 0x5c, (char *) a + 0xe8) <= 0xc000) {
        return 1;
    } else {
        return 0;
    }
}
