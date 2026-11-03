/* place_claim_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020528fc @ 0x020528fc, 0x64 bytes, Thumb
 * func_020528e4 @ 0x020528e4, 0x18 bytes, Thumb
 * func_020528d4 @ 0x020528d4, 0x10 bytes, Thumb
 */

extern int func_02053380(void *a, void *b, unsigned char c, int *d);
extern void func_02073820(void *a);
extern void func_02073770(void *a, int b, void *c);
extern void *data_020ccf94;
extern unsigned char data_021c87fc[];
extern int data_021c8750;
extern void *func_0205340c(void *a, void *b);

void func_020528fc(unsigned char *p, void *q)
{
    int arr[3];
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[0] = p[0] << 9;
    arr[2] = p[1] << 9;
    if (func_02053380((void *) data_021c87fc, q, p[2], arr) != 0) {
        void *obj = data_020ccf94;
        func_02073820(obj);
        func_02073770(obj, 0x1f, q);
    } else {
        void *obj = data_020ccf94;
        func_02073820(obj);
        func_02073770(obj, 0x20, q);
    }
}

void func_020528e4(int arg)
{
    if (arg != 0) {
        data_021c8750 = 1;
    } else {
        data_021c8750 = 2;
    }
}

void *func_020528d4(void *arg)
{
    return func_0205340c((void *) data_021c87fc, arg);
}
