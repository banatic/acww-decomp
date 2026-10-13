/* func_ov134_0229accc @ 0x0229accc, 0x1ac bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov134_0229b884(char *self, int idx);
extern void func_ov134_0229a96c(char *self, int idx, int val);
extern void func_ov134_0229b890(char *self, int idx);
extern void func_ov134_0229b908(char *self);
extern int func_ov134_022995c0(char *self, int mask);
extern void func_ov134_022995a0(char *self, int val);
extern void func_ov134_022995b0(char *self, int val);
extern void func_ov134_0229af60(char *self);
extern void func_ov134_0229af74(char *self, unsigned char a, unsigned char b);
extern void func_0209e234(char *dst, int amt);
extern void func_0209e0c0(char *dst, int amt);
extern int func_0209e3ac(char *a, char *b, int len);
extern int func_0209e350(char *a, char *b);
extern void func_0209e100(char *p, int len);
extern void func_0209e268(char *p, int len);
extern void MI_CpuCopy8(char *dst, const char *src, unsigned int size);

void func_ov134_0229accc(char *self, int amt)
{
    unsigned char arr[6];
    int i;
    int len;
    int flag;
    char *p;

    if (amt == 0) {
        return;
    }

    i = 0;
    do {
        arr[i] = func_ov134_0229b884(self, i);
        i++;
    } while (i <= 4);

    arr[5] = 0;

    if (amt > 0) {
        func_0209e234(self + 0xc0, amt);
    } else {
        func_0209e0c0(self + 0xc0, -amt);
    }

    flag = 1;

    if (func_ov134_022995c0(self, 0x40) != 0) {
        if (func_0209e3ac(self + 0xd0, self + 0xc0, 0x3f) == -1) {
            len = func_0209e350(self + 0xd0, self + 0xc0);
            flag = 0;
            MI_CpuCopy8(self + 0xd0, self + 0xb8, 8);
            func_ov134_022995b0(self, 0x10);
            p = self + 0xc0;
            while (len >= 0x2d0) {
                func_0209e100(p, 0xc);
                len -= 0x2d0;
            }
        } else {
            func_ov134_022995a0(self, 0x10);
        }
    }

    if (func_ov134_022995c0(self, 0x80) != 0) {
        if (func_0209e3ac(self + 0xc8, self + 0xc0, 0x3f) == 1) {
            len = func_0209e350(self + 0xc0, self + 0xc8);
            flag = 0;
            MI_CpuCopy8(self + 0xc8, self + 0xb8, 8);
            func_ov134_022995b0(self, 0x20);
            p = self + 0xc0;
            while (len >= 0x2d0) {
                func_0209e268(p, 0xc);
                len -= 0x2d0;
            }
        } else {
            func_ov134_022995a0(self, 0x20);
        }
    }

    if (flag) {
        MI_CpuCopy8(self + 0xc0, self + 0xb8, 8);
        func_ov134_0229af60(self);
    } else {
        func_ov134_0229af74(self, self[0xc2], self[0xc1]);
    }

    i = 0;
    do {
        if (func_ov134_0229b884(self, i) != arr[i]) {
            (self + i)[0x98] = 0x0a;
            func_ov134_0229a96c(self, i, 5);
            func_ov134_0229b890(self, i);
            if (i >= 0 && i <= 2) {
                arr[5] = 1;
            }
        }
        i++;
    } while (i <= 4);

    if (arr[5] != 0) {
        self[0x9d] = 0x0a;
        func_ov134_0229a96c(self, 5, 5);
        func_ov134_0229b908(self);
    }
}
