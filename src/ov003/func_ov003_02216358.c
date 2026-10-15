/* func_ov003_02216358 @ 0x02216358, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022163f8(void *addr, unsigned char *out);
extern int func_ov003_02216410(void *self, int a, void *out, int b, int c);

void func_ov003_02216358(void *self, int value)
{
    unsigned char status;
    unsigned int tmp[2];

    func_ov003_022163f8((char *) self + 0x8f0, &status);
    if (status == 0) {
        tmp[0] = 0;
        tmp[1] = 0;
        func_ov003_02216410(self, 0, tmp, 6, value);
    }
}
