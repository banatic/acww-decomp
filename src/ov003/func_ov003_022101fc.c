/* func_ov003_022101fc @ 0x022101fc, 0xd4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200faa8(void *p, int n);
extern void func_02010f5c(void *p);
extern void func_0200f2a0(void *p, int n, int *arr);
extern int func_02056f28(void *p, int n);
extern void func_0206026c(void *p, int n);
extern void func_02060428(void *p, int *arr);
extern int func_0200f328(void *p, int n);
extern unsigned int *func_0200f27c(void *p, int n);

typedef struct {
    unsigned int : 12;
    unsigned int field : 16;
    unsigned int : 4;
} Bitfield;

void func_ov003_022101fc(void *p)
{
    int arr[3];
    int arr2[3];

    func_0200faa8(p, 0x400);
    func_02010f5c(p);

    if (*(int *) ((char *) p + 0x704) != 0x5f) {
        return;
    }

    arr[0] = *(int *) ((char *) p + 0x6f4);
    arr[1] = *(int *) ((char *) p + 0x6f8);
    arr[2] = *(int *) ((char *) p + 0x6fc);

    arr[1] += 0xb00;
    arr[2] += 0x300;

    if (((Bitfield *) ((char *) p + 0x2d8))->field < 0xb) {
        func_0200f2a0(p, 0x851, arr);
        return;
    } else {
        if (func_02056f28((char *) p + 0x2d0, 0xb) != 0) {
            func_0206026c((char *) p + 0x5c8, 9);
            arr2[0] = arr[0];
            arr2[1] = arr[1];
            arr2[2] = arr[2];
            func_02060428((char *) p + 0x5c8, arr2);
            func_0200f328(p, 0x852);
            func_0200f328(p, 0x853);
            func_0200f27c(p, 9);
        }
    }
}
