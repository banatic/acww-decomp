/* func_02066198 @ 0x02066198, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003780(void *obj);
extern void func_02003728(void *obj, int value);
extern int func_02003750(void *obj);
extern void func_02066650(void *self);
extern void func_020666e4(void *dst, const void *src);
extern void func_020666b0(void *obj, int val);
extern void func_02065eac(void *obj, int val);
extern void func_020663d4(void *self, int *out, int a, int b, int c);

void func_02066198(void *self, int a2, int a3, int a4, int a5, const unsigned char *a6, int a7, int a8)
{
    int tmp1[4];
    int tmp2[4];

    func_02003780(tmp1);
    func_02003780(tmp2);

    func_02003728(tmp1, a7);
    func_02003728(tmp2, a8);

    func_02066650(self);

    ((unsigned char *) self)[0xf9] = *a6;
    ((unsigned char *) self)[0xfb] = 0;

    func_020666e4((unsigned char *) self + 0x24, tmp1);
    func_020666e4((unsigned char *) self + 4, tmp2);

    if (a5 < 0) {
        func_020666b0((unsigned char *) self + 4, 5);
        a5 = 0;
    }

    func_02065eac(self, 7);

    func_020663d4(self, &a5, a2, a3, a4);

    func_02003750(tmp2);
    func_02003750(tmp1);
}
