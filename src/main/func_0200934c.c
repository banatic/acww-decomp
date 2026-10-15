/* func_0200934c @ 0x0200934c, 0x138 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e110(void);
extern void func_02009498(void *ptr, unsigned char a, unsigned char b, unsigned char c);
extern void func_020109a0(void *self, void *entry, int a, unsigned short b);
extern int func_0200fbe0(void *self);
extern void func_0205eae0(void *ptr, int a, int b, int c);
extern int func_02073908(void *a, unsigned int b);
extern void func_02035624(int arg);
extern void func_02035684(int a, int b, int c);
extern void func_020356c4(int a, int b, int c, int d);

extern void *data_020c7620[];
extern void *data_020ccf94;
extern unsigned short data_020c75f0[];

void func_0200934c(void *self, unsigned char *info, int arg2)
{
    unsigned char b0, b1, b2;
    unsigned char *p = info + 0xc;
    char *base;
    int ret;
    int r7;

    b0 = info[0xc];
    b1 = p[1];
    b2 = p[2];

    if ((unsigned char) (b0 + 0xfe) <= 1) {
        func_0203e110();
    }

    base = (char *) self + 0x7d4;
    base[2] = b0;

    if (b0 == 0) {
        if (arg2 != 0x57) {
            base[3] = 3;
        } else {
            base[3] = 0;
        }
    } else {
        base[3] = 0;
    }

    base[4] = 0;
    base[5] = b1;
    base[6] = b2;

    func_02009498((char *) self + 0x8f0, b0, b1, b2);
    func_020109a0(self, data_020c7620[b0], 3, 0);
    ((char *) self)[0x8eb] = 0;

    // Case bodies are listed in their original layout order.
    ret = func_0200fbe0(self);
    switch (ret) {
        case 4:
            func_0205eae0((char *) self + 0x5a0, 9, 3, 1);
            break;
        case 3:
            func_0205eae0((char *) self + 0x5a0, 0x1f, 3, 1);
            break;
    }

    if (func_02073908(data_020ccf94, *(unsigned int *) ((char *) self + 0x800)) != 0) {
        r7 = 0xd;
        switch (b0) {
            case 0:
            case 1:
                r7 = 6;
                break;
            case 2:
            case 3:
                r7 = 6;
                func_02035624(0x12);
                func_02035684(5, 0, 1);
                *((unsigned int *) ((char *) self + 0x81c)) = 7;
                break;
            default:
                func_02035684(12, 0, 1);
                *((unsigned int *) ((char *) self + 0x81c)) = 7;
        }
        *(unsigned short *) base = data_020c75f0[b0];
        func_020356c4(r7, data_020c75f0[b0], 0x7f, 1);
    }
}