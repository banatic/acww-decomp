/* func_ov072_02279010 @ 0x02279010, 0x88 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */
extern int func_02087178(const void *);
extern int gt2GetIncomingBufferSize(const void *);
extern int func_0201c314(const void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_020147e0(void *, int, int);
extern int func_02019c90(void *, int, int, unsigned short);
extern unsigned short data_020c80f8;

extern unsigned char data_021ebcd2[];

int func_ov072_02279010(void *self)
{
    char *s = (char *) self;
    int tmp;
    int arg2;
    int s16;

    s[0x718] = 0;

    if (func_02087178((const void *) data_021ebcd2) != 0) {
        if (*(int *) (s + 0x720) == 0) {
            tmp = gt2GetIncomingBufferSize(s + 0x658);
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
