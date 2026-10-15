/* func_ov119_0229b284 @ 0x0229b284, 0x108 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229ac80(void *receiver);
extern void func_ov119_0229bba8(void *self, int arg);
extern int func_020984fc(int arg);
extern int func_02099664(int arg);
extern int func_02077bc8(int arg);
extern int func_ov119_0229ac3c(void *self, int arg);
extern void *func_ov119_0229ae50(void *receiver);
extern int func_02099870(int arg);
extern int func_02077c3c(char *elem);
extern int func_02077ea4(int a, int b);
extern int func_020950a8(int arg);
extern int func_02077c38(char *elem);
extern void func_02051c08(int a, int b, int c);
extern int func_02095040(int arg);
extern int func_020642a4(int arg);
extern int func_02077c34(char *elem);
extern int func_020ee45c(void *self);
extern void func_ov090_02298fa4(int arg);
extern int func_ov119_0229ae68(void *receiver);
extern int func_02077d68(int arg);
extern int func_020eaf48(int a, int b);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov119_0229b248(void *self, int arg);

void func_ov119_0229b284(void *self)
{
    int tmp, sp4, sp8, spC, sp10;
    int r4;
    char *r6;
    char *r7;

    r4 = func_ov119_0229ac80((void *) self);
    if (r4 == -1) {
        func_ov119_0229bba8(self, 0x13);
        return;
    }

    tmp = func_020984fc(((unsigned char *) self)[0xad] - 6);
    if (func_ov119_0229ac3c(self, func_02077bc8(func_02099664(tmp)))) {
        func_ov119_0229bba8(self, 0x14);
        return;
    }

    r6 = func_ov119_0229ae50((void *) self);
    sp4 = func_02099870(tmp);
    r7 = r6 + r4 * 0x24;
    sp8 = func_02077c3c(r7);
    func_02077ea4(sp8, func_02077bc8(func_02099664(tmp)));
    spC = func_020950a8(sp4);
    func_02051c08(spC, func_02077c38(r7), 6);
    sp10 = func_020642a4(func_02095040(sp4));
    func_02051c08(sp10, func_02077c34(r7), 6);

    func_ov090_02298fa4(func_020ee45c(self));

    ((unsigned char *) self)[0xb4] = (unsigned char) r4;

    if (func_ov119_0229ae68(self) != 0) {
        if (func_020eaf48(((unsigned char *) self)[0xb4],
                          func_02077d68(func_02077c3c(r6 + ((unsigned char *) self)[0xb4] * 0x24))) == 0) {
            func_ov002_02208098(self, 0x10);
            return;
        }
    }

    func_ov119_0229b248(self, r4);
}
