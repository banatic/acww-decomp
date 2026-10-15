/* func_ov088_02279450 @ 0x02279450, 0x22 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov088_02279474(void *p);

int func_ov088_02279450(void *p)
{
    int v;
    v = *(int *) ((char *) p + 0x98);
    if (v != 0) {
        if (func_ov088_02279474(p) != 0) {
            return 1;
        }
    }
    return 0;
}
