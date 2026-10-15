/* func_ov118_0229ba60 @ 0x0229ba60, 0x38 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_0208e95c(void *ptr, int value);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);
extern void func_ov118_0229abe0(void *ptr);

void func_ov118_0229ba60(void *param)
{
    unsigned short flag;
    void *self = param;

    flag = data_021fbe40;
    if ((flag & 1) == 0) {
        func_0208e95c((char *) self + 0x678, 3);
        func_ov002_02208098(self, 9);
    } else {
        func_ov118_0229abe0(self);
    }
}
