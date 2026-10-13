/* func_ov049_0226262c @ 0x0226262c, 0x38 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *);
extern int func_0201c314(void *, int);
extern void func_020147fc(void *, int, int, int);

int func_ov049_0226262c(void *self)
{
    int size = gt2GetIncomingBufferSize((char *) self + 0x658);
    int ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_020147fc((char *) self + 0x618, 0, ret, 1);
    return 1;
}
