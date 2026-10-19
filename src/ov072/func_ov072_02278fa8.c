/* func_ov072_02278fa8 @ 0x02278fa8, 0x68 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016104(void *p);
extern int func_0201c314(void *p, int a);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(const unsigned char *p);
extern int func_0203e020(void *p);
extern void func_ov072_02279628(void *p, int a);

int func_ov072_02278fa8(char *self)
{
    int size;
    int s;

    if (*(int *) (self + 0x720) != 0) {
        size = func_02016104(self + 0x658);
        s = *(short *) (self + 0x8e);
        if (size != 0) {
            s = func_0201c314(self, size);
        }
        func_020147fc(self + 0x618, 0, s, 0);
        *(int *) (self + 0x720) = 0;
    }

    if (!func_02014868((unsigned char *) (self + 0x618))) {
        func_0203e020(self);
        func_ov072_02279628(self, 3);
    }
    return 1;
}
