/* func_ov094_0229af40 @ 0x0229af40, 0x78 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b0d4(void *);
extern void func_ov094_0229a38c(void *);

void func_ov094_0229af40(void *self, int param)
{
    func_ov094_0229b0d4((char *) self + 0x184);
    func_ov094_0229a38c((char *) self + 0xa38);
    func_ov094_0229a38c((char *) self + 0xa40);
    func_ov094_0229a38c((char *) self + 0xa48);
    ((char *) self)[0xa56] = 0x23;
    ((char *) self)[0xa57] = 0;
    *(int *) ((char *) self + 0xa50) = param;
    *(int *) ((char *) self + 0xa34) = 0;
    ((char *) self)[0xa59] = 0xa;
    ((char *) self)[0xa5c] = 1;
}
