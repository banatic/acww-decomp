/* func_ov119_0229c090 @ 0x0229c090, 0xac bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov119_0229a4e4(void *);
extern int func_ov002_02208054(void *, int);
extern void func_ov119_0229b828(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208b00(void *, unsigned char, unsigned char);
extern int func_ov119_0229a420(void *, int);
extern void func_ov002_02209114(void *, int, int);
extern int func_ov119_0229a5cc(void *, int);

void func_ov119_0229c090(void *self)
{
    int r;
    int v;
    int w;

    if (func_0206f56c() != 0) {
        func_ov119_0229a4e4(self);
        return;
    }

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov119_0229b828(self);
        func_ov002_02208098(self, 6);
        return;
    }

    r = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (r == 0) {
        return;
    }

    v = func_ov002_02208b00((char *) self + 0xdc, data_021f6c58, data_021f6c54);
    if (v < 0) {
        return;
    }

    w = func_ov119_0229a420(self, 0x10);
    if (w != 0 && v == 0) {
        return;
    }

    func_ov002_02209114((char *) self + 0xdc, v, 1);
    ((char *) self)[0xad] = (char) func_ov119_0229a5cc(self, v);
    func_ov002_02208098(self, 0xb);
}
