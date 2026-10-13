/* func_ov004_022316a4 @ 0x022316a4, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022316a4;
typedef void (UnkStruct_022316a4::*PMF)(void);
struct UnkStruct_022316a4 {};
struct UnkStruct_022316a4_2 {
    int a, b;
    PMF fn;
};
extern "C" {
extern UnkStruct_022316a4_2 data_ov004_022588d8[];
extern void func_02055124(void *);
}

extern "C" int func_ov004_022316a4(UnkStruct_022316a4 *self)
{
    int i = *(int *) ((char *) self + 0x638);
    if (data_ov004_022588d8[i].fn != 0) {
        (self->*(data_ov004_022588d8[i].fn))();
    }
    func_02055124((char *) self + 0xec);
    return 1;
}
