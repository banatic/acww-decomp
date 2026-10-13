/* func_ov107_0229cfe4 @ 0x0229cfe4, 0x70 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov107_0229d29c(void *self, unsigned char b);
extern int func_ov107_0229d260(void *self, unsigned char b);
extern int func_0206fe54(void);
extern void func_0208aa60(void *dst, int a, int b);
extern int func_ov107_0229d388(void *self, unsigned char b);
extern int func_ov107_0229d36c(void *self, unsigned char b);
extern void func_ov094_0229abb8(void *a, void *b, int c);

void func_ov107_0229cfe4(void *self)
{
    int a, b;
    a = func_ov107_0229d29c(self, *(unsigned char *) ((char *) self + 0xb7)) - 0x6d;
    b = func_ov107_0229d260(self, *(unsigned char *) ((char *) self + 0xb7)) - 0x78;
    if (func_0206fe54()) {
        b -= 8;
    }
    func_0208aa60((char *) self + 0x21cc, a, b);
    if (func_ov107_0229d388(self, *(unsigned char *) ((char *) self + 0xb7))) {
        int c;
        c = func_ov107_0229d36c(self, *(unsigned char *) ((char *) self + 0xb7));
        func_ov094_0229abb8((char *) self + 0x10c, (char *) self + 0x21cc, c);
    }
}
