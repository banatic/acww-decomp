/* func_ov119_0229bc74 @ 0x0229bc74, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229ae50(const void *p);
extern int func_02077c3c(int a);
extern int func_02077d68(int a);
extern int func_020eaf48(unsigned char a, int b);
extern void func_ov119_0229b248(const void *p, unsigned char b);

void func_ov119_0229bc74(const unsigned char *self)
{
    int v;

    v = func_ov119_0229ae50(self);
    v += self[0xb4] * 36;
    v = func_02077c3c(v);
    v = func_02077d68(v);
    if (func_020eaf48(self[0xb4], v) != 0) {
        func_ov119_0229b248(self, self[0xb4]);
    }
}
