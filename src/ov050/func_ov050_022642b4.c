/* func_ov050_022642b4 @ 0x022642b4, 0x50 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(const void *p);
extern int func_0201c314(void *p, int size);
extern int func_020147fc(void *a, int b, int c, int d);
extern int func_ov050_02260510(void *p);
extern int func_0208602c(void);
extern int func_020860d0(int argument0);
extern void func_02087f0c(void *argument0);

int func_ov050_022642b4(void *p)
{
    int size;
    int r2;

    size = gt2GetIncomingBufferSize((char *) p + 0x658);
    r2 = 0;
    if (size != 0) {
        r2 = func_0201c314(p, size);
    }
    func_020147fc((char *) p + 0x618, 0, r2, 1);
    if (func_ov050_02260510(p) != 0) {

        func_02087f0c((void *) func_020860d0(func_0208602c()));
    }
    return 1;
}
