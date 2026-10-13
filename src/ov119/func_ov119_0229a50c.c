/* func_ov119_0229a50c @ 0x0229a50c, 0x54 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(void *a, void *b, int c);
extern void func_ov002_022098ec(void *a, int b, int c);
extern void func_ov002_0220970c(void *a, int b);
extern void func_ov002_02208098(void *a, int b);
extern void func_ov119_0229a400(void *a, int b);

void func_ov119_0229a50c(void *self, int arg2)
{
    int size;
    func_ov002_02208c58((char *) self + 0xdc, (char *) self + 0x4c4, arg2);
    size = (*(unsigned char *) ((char *) self + 0xa0) == 0x16) ? 0x9c : 0xb8;
    func_ov002_022098ec((char *) self + 0xdc, 0x100, size);
    func_ov002_0220970c((char *) self + 0xdc, 0);
    func_ov002_02208098(self, 0xa);
    func_ov119_0229a400(self, 0x10);
}
