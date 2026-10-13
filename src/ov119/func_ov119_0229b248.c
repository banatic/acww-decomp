/* func_ov119_0229b248 @ 0x0229b248, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229adc4(void *self, void *other);
extern int func_ov119_0229a650(void *self, void *other);
extern void func_ov119_0229a69c(void *self, int r);
extern void func_ov119_0229a714(void *self);
extern void func_ov119_0229bbe4(void *self);

void func_ov119_0229b248(void *self, void *other)
{
    int r;
    func_ov119_0229adc4(self, other);
    r = func_ov119_0229a650(self, other);
    if (r != ((unsigned char *) self)[0x9d]) {
        func_ov119_0229a69c(self, r);
    } else {
        func_ov119_0229a714(self);
    }
    func_ov119_0229bbe4(self);
}
