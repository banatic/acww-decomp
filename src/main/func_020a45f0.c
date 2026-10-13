/* func_020a45f0 @ 0x020a45f0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *func_020682e0(int);
extern void func_02068320(int *);
extern int func_020b5e10(int);
extern int func_020b63f4(int, int, void *, int, int, int, int);
extern void func_020a4e94(int, int);

typedef struct {
    int a[3];
} UnkStruct_020a45f0;
extern UnkStruct_020a45f0 data_020d1bfc;

void func_020a45f0(int param)
{
    int *p;
    UnkStruct_020a45f0 local;

    p = func_020682e0(0);
    if (p[1] == 0) {
        func_02068320(p);
        local.a[0] = data_020d1bfc.a[0];
        local.a[1] = data_020d1bfc.a[1];
        func_020b63f4(func_020b5e10(local.a[2] = data_020d1bfc.a[2]), 13, &local, 0x00800000, 0, 3, 2);
        func_020a4e94(param, 0);
    }
}
