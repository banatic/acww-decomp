/* func_ov004_02230078 @ 0x02230078, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02230078 {
    int a;
    ~UnkStruct_02230078() {}
};

typedef struct {
    int m[12];
} Mtx;
extern "C" {
extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern Mtx data_021fbe48;
extern void func_020e96c8(Mtx *, int, int, int);
extern void func_ov004_0222fef8(void *);
}
extern "C" int func_ov004_02230078(char *self)
{
    UnkStruct_02230078 t;
    func_02055124(self + 0xec);
    func_02055124(self + 0x290);
    func_02056ffc(self + 0x418);
    **(int **) (self + 0x430) = *(int *) (self + 0x420);
    func_020e96c8(&data_021fbe48, *(int *) (self + 0x5c), *(int *) (self + 0x60), *(int *) (self + 0x64));
    *(Mtx *) (self + 0x150) = data_021fbe48;
    *(Mtx *) (self + 0x2f4) = data_021fbe48;
    func_ov004_0222fef8(self);
    return 1;
}
