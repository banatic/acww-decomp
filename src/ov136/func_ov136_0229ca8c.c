/* func_ov136_0229ca8c @ 0x0229ca8c, 0x28 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov136_0229c668(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov136_0229ca8c(void *self)
{
    if (func_0208e484((char *) self + 0x94)) {
        func_ov136_0229c668(self);
        func_ov002_02208098(self, ((unsigned char *) self)[0x2b76]);
    }
}
