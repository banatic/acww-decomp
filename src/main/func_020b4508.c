/* func_020b4508 @ 0x020b4508, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Modf(int, int *);
extern int func_020b45d0(void *, int, int, int, int, int);
extern void *func_020b5630(void *);
extern void *func_020a8228(void *);
extern int func_020a8bb8(void *, void *);
extern int func_020a89f8(void *, void *);
extern int func_020a89dc(void *, void *);
extern void *func_020a8210(void *);
extern void *func_020b5618(void *);

extern int data_020d2080;

typedef struct {
    char data[0x40];
} UnkStruct_020b4508;
typedef struct {
    char data[0x40];
} UnkStruct_020b4508_2;
typedef struct {
    char data[0x5c];
} UnkStruct_020b4508_3;

int func_020b4508(void *p, int q, int n)
{
    int local;
    UnkStruct_020b4508 A;
    UnkStruct_020b4508_2 B;
    UnkStruct_020b4508_3 C;
    int i;
    int acc;
    int shifted;
    int flag;
    int result;
    int ret;

    acc = FX_Modf(q, &local);

    for (i = 0; i < n; i++) {
        acc = acc * 10;
    }

    shifted = local >> 12;

    func_020b5630(&A);
    func_020b5630(&B);
    func_020a8228(&C);

    ret = func_020b45d0(&A, shifted, 10, 0, 0, 0);
    flag = (ret & 1) ? 1 : 0;

    ret = func_020b45d0(&B, acc >> 12, 10, 0, 0, 0);
    result = (flag & ret) ? 1 : 0;

    ret = func_020a8bb8(p, &A);
    result = (result & ret) ? 1 : 0;

    ret = func_020a89f8(p, &data_020d2080);
    result = (result & ret) ? 1 : 0;

    ret = func_020a89dc(p, &B);
    result = (result & ret) ? 1 : 0;

    func_020a8210(&C);
    func_020b5618(&B);
    func_020b5618(&A);

    return result;
}
