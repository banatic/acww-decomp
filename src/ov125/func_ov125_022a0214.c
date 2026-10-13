/* func_ov125_022a0214 @ 0x022a0214, 0xa0 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *a, int b);
extern void func_ov125_0229f948(void *a);
extern void func_ov002_02208098(void *a, int b);
extern int func_ov002_02208b00(void *a, u8 b, u8 c);
extern void func_ov002_02209114(void *a, int b, int c);
extern u8 func_ov125_0229fc84(void *a, int b);

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;

struct MyObj {
    u8 data[0x880];
};

void func_ov125_022a0214(struct MyObj *obj)
{
    if (func_ov002_02208054(obj, 1) != 0) {
        func_ov125_0229f948(obj);
        func_ov002_02208098(obj, 3);
        obj->data[0x87c] = obj->data[0x87b];
    } else {
        unsigned int flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (flag != 0) {
            int idx = func_ov002_02208b00(&obj->data[0x180], data_021f6c58, data_021f6c54);
            if (idx >= 0) {
                func_ov002_02209114(&obj->data[0x180], idx, 1);
                obj->data[0x87d] = func_ov125_0229fc84(obj, idx);
                func_ov002_02208098(obj, 8);
            }
        }
    }
}
