/* func_0205e444 @ 0x0205e444, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct RetStruct {
    unsigned char pad_00[13];
    unsigned char unk_0D;
};
extern struct RetStruct *func_0205e14c(void *p, int n);
extern void func_020b9ec4(struct RetStruct *);
extern void func_020ba004(struct RetStruct *);

void func_0205e444(void *p)
{
    int flag;
    flag = (func_0205e14c(p, 0)->unk_0D == 1);
    if (flag) {
        func_020b9ec4(func_0205e14c(p, 0));
    } else {
        func_020ba004(func_0205e14c(p, 0));
    }
    flag = (func_0205e14c(p, 1)->unk_0D == 1);
    if (flag) {
        func_020b9ec4(func_0205e14c(p, 1));
    } else {
        func_020ba004(func_0205e14c(p, 1));
    }
}
