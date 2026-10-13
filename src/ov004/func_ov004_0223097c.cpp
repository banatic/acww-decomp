/* func_ov004_0223097c @ 0x0223097c, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0223097c {
    int a;
    ~UnkStruct_0223097c() {}
};

typedef struct {
    int m[12];
} Mtx;
extern "C" {
extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern Mtx data_021fbe48;
extern void func_020e96c8(Mtx *, int, int, int);
extern void func_ov004_02230780(void *);
}
extern "C" int func_ov004_0223097c(char *self)
{
    UnkStruct_0223097c t;
    func_02055124(self + 0x400);
    func_02056ffc(self + 0x6b4);
    **(int **) (self + 0x6cc) = *(int *) (self + 0x6bc);
    func_020e96c8(&data_021fbe48, *(int *) (self + 0x5c), *(int *) (self + 0x60), *(int *) (self + 0x64));
    *(Mtx *) (self + 0x3ac) = data_021fbe48;
    *(Mtx *) (self + 0x464) = data_021fbe48;
    func_ov004_02230780(self);
    return 1;
}
