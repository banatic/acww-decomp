/* func_ov050_02264364 @ 0x02264364, 0x78 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099020(int, int);
extern int func_ov050_02260510(void *);
extern int func_0202ea40(void *, void *, int);

int func_ov050_02264364(void *self)
{
    int size;
    int arg2;
    int a;
    int local;

    size = func_02016104((char *) self + 0x658);
    arg2 = 0;
    if (size != 0) {
        arg2 = func_0201c314(self, size);
    }

    func_020147fc((char *) self + 0x618, 0, arg2, 0);

    a = func_020984e8();
    func_02099640(a);

    if (func_02099020(a, 1) != 0) {
        return 1;
    }

    if (func_ov050_02260510(self) != 0) {
        if (func_0202ea40(self, &local, 3) != 0) {
            ((unsigned char *) self)[0x72c] = 1;
        }
    }
    return 1;
}
