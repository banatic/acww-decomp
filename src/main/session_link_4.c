/* session_link_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02074e48 @ 0x02074e48, 0x1a bytes, Thumb
 * func_02074dfc @ 0x02074dfc, 0x4c bytes, Thumb
 * func_02074d60 @ 0x02074d60, 0x9c bytes, Thumb
 * func_02074d24 @ 0x02074d24, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_00[0x6c];
    unsigned char unk_6C;
} UnkStruct_02074d60;

extern unsigned func_020a6f64(int);
extern int data_020ccf94;
extern char *func_02073d28(int, int);
extern void func_02077b3c(void *, int, int);
extern int func_020740b4(void);
extern int func_02073dd4(UnkStruct_02074d60 *p, int a);
extern void func_020a7394(int a, int b, int c, int d, int e);
extern void func_02073de0(UnkStruct_02074d60 *p, int a, int b);
extern void func_020738f4(UnkStruct_02074d60 *p, unsigned char b);
extern void func_02073cb8(UnkStruct_02074d60 *p, int a);
extern void func_02073c74(UnkStruct_02074d60 *p, int a, int b);
extern void func_020a6c6c(int a);
extern void func_02075104(int a);
extern unsigned int func_0207762c(int);
extern void func_0205cb68(int, int);
extern void func_020ecf20(void);

int func_02074e48(int argument0)
{
    return (func_020a6f64((int) argument0) - 5) <= 1 ? 1 : 0;
}

int func_02074dfc(int arg)
{
    int result = 0;
    if (func_02074e48(arg)) {
        char *p;
        int t1, t2;
        p = func_02073d28(data_020ccf94, arg);
        func_02077b3c(p, result, 6);
        t1 = (int) func_020a6f64(arg);
        t2 = func_020740b4();
        p[1] = (char) ((t1 & 7) | ((t2 << 4) & 0xf0));
        result += 2;
    }
    return result;
}

void func_02074d60(int param0)
{
    int i;
    UnkStruct_02074d60 *loopPtr;
    UnkStruct_02074d60 *p;

    i = 3;
    loopPtr = (*(UnkStruct_02074d60 **) &data_020ccf94);

    do {
        if (func_02073dd4(loopPtr, i) != 0) {
            if (i == 0) {
                func_020a7394(0, 0x3f, 1, 0, 2);
            } else {
                func_020a7394(i, 0x3f, 0, 0, 2);
            }
        }
        i--;
    } while (i >= 0);

    func_020a7394(param0, 0x3f, 0, 0, 7);

    p = (*(UnkStruct_02074d60 **) &data_020ccf94);
    func_02073de0(p, param0, 0);
    func_020738f4(p, (unsigned char) (p->unk_6C - 1));
    func_02073cb8(p, param0);
    func_02073c74(p, param0, 0);
    func_020a6c6c(param0);
    func_02075104(-param0);
}

void func_02074d24(int arg)
{
    unsigned int max = 0;
    int i = 0x45;
    unsigned int ret;

    do {
        ret = func_0207762c(i);
        if (ret > max) {
            max = ret;
        }
        i--;
    } while (i >= 0);

    (*(unsigned char **) &data_020ccf94)[0x6d] = max;
    (func_0205cb68(0x4b000, arg), func_020ecf20());
}
