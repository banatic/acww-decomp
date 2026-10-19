/* func_ov068_0226e81c @ 0x0226e81c, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);

int func_ov068_0226e81c(void *self)
{
    int size = func_02016104((char *) self + 0x658);
    int ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_020147fc((char *) self + 0x618, 0, ret, 1);
    return 1;
}
