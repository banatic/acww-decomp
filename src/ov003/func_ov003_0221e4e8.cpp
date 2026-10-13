/* func_ov003_0221e4e8 @ 0x0221e4e8, 0x98 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct ClassType;

typedef void (ClassType::*PMF)();

struct ClassType {
    char pad_00[0x2b4];
    int index;
};

extern PMF data_ov003_0223941c, data_ov003_022393cc, data_ov003_022393d4, data_ov003_02239404, data_ov003_022393e4;

extern "C" void func_ov003_0221e4e8(ClassType *obj)
{
    static PMF pmf_arr[5] = {data_ov003_0223941c, data_ov003_022393cc, data_ov003_022393d4, data_ov003_02239404,
                             data_ov003_022393e4};
    if (obj->index >= 5) {
        return;
    }
    (obj->*pmf_arr[obj->index])();
}
