/* func_ov049_02260c94 @ 0x02260c94, 0x64 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c2bc(void);
extern int func_ov004_0223b39c(int a, int b);
extern void *func_020960f8(int size, int align);
extern void func_02068434(void *p);
extern void func_0206844c(void *p, char *c, void *q);
extern void func_ov049_022610c4(void *p, int x);
extern void *data_ov049_02263298;

typedef struct {
    char pad_00[0x728];
    int a;
    int b;
} UnkStruct_02260c94;

typedef struct {
    char pad_00[0x40];
    void *p;
    char pad_44[0x6c];
    UnkStruct_02260c94 *sub;
} UnkStruct_02260c94_2;

void func_ov049_02260c94(UnkStruct_02260c94_2 *arg)
{
    char c;
    if (func_ov004_0222c2bc() != 0) {
        UnkStruct_02260c94 *sub = arg->sub;
        func_ov004_0223b39c(sub->a, sub->b);
    }
    if (func_020960f8(16, 4) != 0) {
        void *p = arg->p;
        func_02068434(p);
        c = '-';
        func_0206844c(p, &c, data_ov049_02263298);
        func_ov049_022610c4(arg, 0);
    }
}
