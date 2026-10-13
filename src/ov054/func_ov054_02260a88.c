/* func_ov054_02260a88 @ 0x02260a88, 0xa8 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_02099020(void *, int);
extern int func_02060d3c(void *);
extern int func_ov054_02260484(void *);
extern void func_0202eac8(void *, int, int, int);
extern void func_02068388(void *, int);
extern const int data_ov054_022629b4[];
extern const int data_ov054_02262f50[];

extern unsigned char data_021ebcd4[];

void func_ov054_02260a88(void *obj)
{
    void *h, *sub;
    int st;

    sub = *(void **) ((char *) obj + 0x40);
    h = func_020984e8();
    *(int *) ((char *) obj + 0xb4) = 0;
    if (func_0202e9fc() == 0) {
        *(int *) ((char *) obj + 0xb4) = 2;
    } else if (func_02099020(h, 1) == 0 && func_02060d3c((void *) data_021ebcd4) != 0) {
        if (func_ov054_02260484(*(void **) ((char *) obj + 0xb0)) != 0) {
            *(int *) ((char *) obj + 0xb4) = 4;
        } else {
            *(int *) ((char *) obj + 0xb4) = 1;
        }
    } else {
        if (func_ov054_02260484(*(void **) ((char *) obj + 0xb0)) != 0) {
            *(int *) ((char *) obj + 0xb4) = 3;
        }
    }
    st = *(int *) ((char *) obj + 0xb4);
    func_0202eac8(obj, data_ov054_02262f50[st], data_ov054_022629b4[st], data_ov054_022629b4[st] - 1);
    func_02068388(sub, 1);
}
