/* func_ov105_0229d59c @ 0x0229d59c, 0x40 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(void *, void *);
extern int func_ov105_0229d75c(void *, void *);
extern int func_ov105_0229d718(void *, void *);
extern int func_ov094_0229b8d8(void *, int);

int func_ov105_0229d59c(void *a, void *b)
{
    if (func_ov105_0229d76c(a, b) != 0 || func_ov105_0229d75c(a, b) != 0) {
        int tmp = func_ov105_0229d718(a, b);
        return func_ov094_0229b8d8((char *) a + 0xd5c, tmp);
    }
    return 0;
}
