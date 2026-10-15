/* func_ov003_02213bf0 @ 0x02213bf0, 0xe0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(const void *);
extern void *func_0205e8e4(const void *);
extern unsigned char func_ov003_0222e538(int v, unsigned char unused);
extern int func_ov003_0222e5fc(int);
extern void *func_ov003_02213ae4(const void *, int, int, int, int, int);
extern unsigned int func_02008258(const void *, unsigned int);
extern int func_02073908(const void *, unsigned int);
extern int func_0200d4e8(const void *, int, int, int);
extern void *data_020ccf94;

void func_ov003_02213bf0(char *self)
{
    unsigned char *p;
    unsigned char v, t;
    int r;

    if (func_02056f94(self + 0x2d0) == 0 && *(unsigned int *) (self + 0x2e0) != 0) {
        return;
    }

    p = (unsigned char *) (self + 0x7d4);
    if (*p != 0) {
        v = *(p + 4);
        if (v == 0xff) {
            func_ov003_02213ae4(self, 0, v, 0x30, 6, -1);
        } else {
            r = func_ov003_0222e538(v, (unsigned char) *(unsigned int *) (self + 0x800));
            if (r == 0) {
                t = (unsigned char) func_ov003_0222e5fc(v);
                func_ov003_02213ae4(self, 0, v, t, 6, -1);
            } else if (r == 1) {
                *p = 0;
            }
        }
    } else {
        if (func_02056f94((char *) func_0205e8e4(self + 0x5a0) + 0x9c) != 0) {
            *(unsigned int *) (self + 0x7fc) = func_02008258(self, *(unsigned int *) (self + 0x7f0));
            if (func_02073908(data_020ccf94, *(unsigned int *) (self + 0x800)) != 0) {
                func_0200d4e8(self, 9, 1, -1);
            }
        }
    }
}
