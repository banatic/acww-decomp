/* func_ov119_0229a49c @ 0x0229a49c, 0x48 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229a46c(void *);
extern void func_0206fdd4(void *, int, int, int, int, int);

void func_ov119_0229a49c(void *self)
{
    int i;

    func_ov119_0229a46c(self);
    for (i = 0; i < 8; i++) {
        if (((unsigned char *) self)[0xb2] & (1 << i)) {
            int d = i * 2;
            func_0206fdd4((unsigned char *) self + 0xe0c, 3, d + 6, 4, d + 7, 5);
        }
    }
}
