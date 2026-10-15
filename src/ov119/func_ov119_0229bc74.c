/* func_ov119_0229bc74 @ 0x0229bc74, 0x3c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov119_0229ae50(void);
extern void *func_02077c3c(void *object);
extern int func_02077d68(void *object);
extern int func_020eaf48(unsigned char a, int b);
extern void func_ov119_0229b248(const void *p, unsigned char b);

void func_ov119_0229bc74(const unsigned char *self)
{
    int v;

    v = (int) func_ov119_0229ae50();
    v += self[0xb4] * 36;
    v = (int) func_02077c3c((void *) v);
    v = func_02077d68((void *) v);
    if (func_020eaf48(self[0xb4], v) != 0) {
        func_ov119_0229b248(self, self[0xb4]);
    }
}
