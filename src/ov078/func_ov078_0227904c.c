/* func_ov078_0227904c @ 0x0227904c, 0x3c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *p);
extern int func_0201c314(void *p, int a);
extern int func_020147fc(void *p, int a, int b, int c);

int func_ov078_0227904c(char *self)
{
    int size;
    int s;

    size = gt2GetIncomingBufferSize(self + 0x658);
    s = *(short *) (self + 0x8e);

    if (size != 0) {
        s = func_0201c314(self, size);
    }

    func_020147fc(self + 0x618, 0, s, 0);
    return 1;
}
