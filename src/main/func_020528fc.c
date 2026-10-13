/* func_020528fc @ 0x020528fc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02053380(void *a, void *b, unsigned char c, int *d);
extern void func_02073820(void *a);
extern void func_02073770(void *a, int b, void *c);
extern void *data_020ccf94;

extern unsigned char data_021c87fc[];

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
