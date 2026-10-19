/* func_02011520 @ 0x02011520, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern int func_02096124(int size, int kind);
extern int func_02095794(int);
extern int func_02030890(int *);
extern void func_020953c4(int *);
extern int func_020b5e10(void);
extern int func_020b6044(int, int, int *, int *);
extern void func_020953a4(int *);
extern int func_0209d780(int);
extern int func_020b67ac(void);
extern int func_0203e110(void);
extern int func_0203e420(void);
extern int func_02096190(int);
extern int func_0203e444(int, int);

int func_02011520(int param)
{
    int a;
    int v;
    int c;
    int ret;

    ret = func_02073908(data_020ccf94, param);
    if (ret == 0) {
        return ret;
    }

    ret = func_02096124(0xb, param);
    if (ret != 0) {
        return ret;
    }

    ret = func_02096124(0x13, param);
    if (ret != 0) {
        return ret;
    }

    ret = func_02096124(5, param);
    if (ret != 0) {
        return ret;
    }

    ret = func_02095794(4);
    if (ret == 0) {
        return ret;
    }

    v = func_02030890((int *) ret);
    if (v == -1) {
        return v;
    }

    func_020953c4(&v);

    ret = func_020b5e10();
    ret = func_020b6044(ret, v, &c, &a);
    if (ret == 0) {
        return ret;
    }

    func_020953a4(&c);

    if (c == 1 || c == 2 || c == 4 || func_0209d780(v) != 0) {
        if (func_020b67ac() != 0) {
            func_0203e110();
        }
        return func_0203e420();
    } else {
        ret = func_02096190(4);
        return func_0203e444(ret, v);
    }
}
