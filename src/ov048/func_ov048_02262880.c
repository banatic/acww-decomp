/* func_ov048_02262880 @ 0x02262880, 0x32 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a193c(void);
extern int func_020b5e10(void);
extern int func_020b6434(int a, int b, int c, int d);
extern void func_ov048_022635f4(void *a, int b);

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02262880;

extern UnkStruct_02262880 *func_020682e0(int a);

int func_ov048_02262880(void *arg)
{
    UnkStruct_02262880 *p;
    int x;

    p = func_020682e0(0);
    if (p->unk_04 == 5) {
        func_020a193c();
        x = func_020b5e10();
        func_020b6434(x, 0x2e, 2, 3);
        func_ov048_022635f4(arg, 3);
    }
    return 1;
}
