/* func_ov003_0220dc0c @ 0x0220dc0c, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *p, int v);
extern int func_02073908(int a, int b);
extern int func_02099e9c(unsigned short *p);
extern void func_0200f268(void *p, int _x);
extern int func_02095694(int a, int b);
extern void func_0209a050(int a);
extern int func_ov003_02217c5c(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_0200d4e8(void *p, int a, int b, int c);
extern int data_020ccf94;

void func_ov003_0220dc0c(void *self)
{
    unsigned short local;

    if (func_02056f94((unsigned char *) self + 0x2d0) == 0) {
        return;
    }

    local = 0x137d;
    *(int *) ((unsigned char *) self + 0x7fc) = func_02008258(self, *(int *) ((unsigned char *) self + 0x7f0));

    if (func_02073908(data_020ccf94, *(int *) ((unsigned char *) self + 0x800)) != 0) {
        int r;

        r = func_02099e9c(&local);
        if (r != -1) {
            func_0200f268(self, 0);
            func_02095694(0x15, *(int *) ((unsigned char *) self + 0x800));
            func_0209a050(r);
            func_ov003_02217c5c(self, 2, 2, 0, 0, 0, 6, -1);
            return;
        }
    }
    func_0200d4e8(self, 3, 1, -1);
}