/* func_0202d8f8 @ 0x0202d8f8, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(void);
extern int func_02080728(void *, int);
extern int func_02080500(void *);
extern int func_020807c0(void *);
extern void func_02081e94(int, int, int, int);
extern void func_02078974(void *, int);
extern void func_02081e14(int, int, int, int);
extern void func_020788f4(void *, int);

struct UnkStruct_0202d8f8 {
    char pad_00[0x13c];
    unsigned char flag;
};

void func_0202d8f8(struct UnkStruct_0202d8f8 *obj, int *out2, int *out3, void *arg4, int flag)
{
    if (obj->flag != 0) {
        return;
    }
    if (flag == 0) {
        if (func_020984e8() != 0) {
            func_020984e8();
            flag = func_02099870();
        }
    }
    if (flag == 0) {
        return;
    }
    if (arg4 == 0) {
        return;
    }
    if (*out2 == 0) {
        *out3 = func_02080728(arg4, flag);
        if (*out3 != -1) {
            return;
        }
        *out3 = func_02080500(arg4);
        if (*out3 == -1) {
            return;
        }
        *out2 = func_020807c0(arg4);
        func_02081e94(*out2, flag, 0, 0);
        func_02078974(arg4, *out3);
    } else {
        func_02081e14(*out2, flag, 0, 0);
        func_020788f4(arg4, *out3);
    }
}
