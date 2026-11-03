/* session_villager: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207835c @ 0x0207835c, 0x24 bytes, Thumb
 * func_02078310 @ 0x02078310, 0x4c bytes, Thumb
 * func_020782d8 @ 0x020782d8, 0x38 bytes, Thumb
 */

typedef struct {
    short arr[4];
    unsigned char ch;
} Src;

extern short func_02077898(const short *p);
extern void *data_020ccf94;
extern int func_02073d90(void *obj);
extern void func_02078380(void *dest, void *src1, void *src2);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *buf, int len);
extern void func_02073770(void *obj, int a, int b);
extern int func_0207f294(int);
extern int func_0207cf74(int);

void func_0207835c(int *dest, short *out, const Src *src)
{
    int i;
    short *p = out;
    *dest = src->ch;
    for (i = 0; i < 4; i++) {
        *p++ = func_02077898(&src->arr[i]);
    }
}

void func_02078310(void *arg0, void *arg1)
{
    int local[3];
    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    if (arg1 == 0) {
        return;
    }
    func_02078380(local, arg0, arg1);
    {
        void *obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, local, 9);
        func_02073770(obj, 0x3b, 4);
    }
}

void func_020782d8(int param0, int param1)
{
    int x;
    if (func_02073d90((void *) ((*(int *) &data_020ccf94)))) {
        x = func_0207f294(param0);
        if (func_0207cf74(x)) {
            func_02078310((void *) x, (void *) param1);
        }
    }
}
