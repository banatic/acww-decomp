/* gull_2: 3 functions, module ov072
 * mwccarm 1.2/base -O4,s
 * func_ov072_02279010 @ 0x02279010, 0x88 bytes, Thumb
 * func_ov072_02278fa8 @ 0x02278fa8, 0x68 bytes, Thumb
 * func_ov072_02278fa4 @ 0x02278fa4, 0x4 bytes, Thumb
 */

extern int func_02087178(const void *);
extern int func_02016104(const void *);
extern int func_0201c314(const void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_020147e0(void *, int, int);
extern int func_02019c90(void *, int, int, unsigned short);
extern unsigned short data_020c80f8;
extern unsigned char data_021ebcd2[];
extern int func_02014868(const unsigned char *p);
extern int func_0203e020(void *p);
extern void func_ov072_02279628(void *p, int a);

int func_ov072_02279010(void *self)
{
    char *s = (char *) self;
    int tmp;
    int arg2;
    int s16;

    s[0x718] = 0;

    if (func_02087178((const void *) data_021ebcd2) != 0) {
        if (*(int *) (s + 0x720) == 0) {
            tmp = func_02016104(s + 0x658);
            s16 = *(signed short *) (s + 0x8e);
            if (tmp == 0) {
                arg2 = s16;
            } else {
                arg2 = func_0201c314(self, tmp);
            }
            func_020147fc(s + 0x618, 0, arg2, 0);
        } else {
            func_02019c90(s + 0x564, 1, 0, data_020c80f8);
        }
    } else {
        func_020147e0(s + 0x618, 0, 0);
    }

    return 1;
}

int func_ov072_02278fa8(char *self)
{
    int size;
    int s;

    if (*(int *) (self + 0x720) != 0) {
        size = func_02016104((const void *) (self + 0x658));
        s = *(short *) (self + 0x8e);
        if (size != 0) {
            s = func_0201c314((const void *) self, size);
        }
        func_020147fc(self + 0x618, 0, s, 0);
        *(int *) (self + 0x720) = 0;
    }

    if (!func_02014868((unsigned char *) (self + 0x618))) {
        func_0203e020(self);
        func_ov072_02279628(self, 3);
    }
    return 1;
}

int func_ov072_02278fa4(void)
{
    return 1;
}
