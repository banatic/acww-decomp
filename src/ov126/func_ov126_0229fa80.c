/* func_ov126_0229fa80 @ 0x0229fa80, 0x90 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02062fbc(void *);
extern void func_02070c08(void *);
extern void func_02062ea4(void *, u16 const *);
extern void func_020a8bb8(void *, void *);
extern int func_020707e8(void *, void *, int);
extern void func_0206fc80(int);
extern void func_0206fc4c(int);
extern void func_02070be8(void *);
extern void func_02062f4c(void *);

typedef struct {
    u32 data[10];
} UnkStruct_0229fa80;
typedef struct {
    u32 data[28];
} UnkStruct_0229fa80_2;

void func_ov126_0229fa80(u8 *param)
{
    UnkStruct_0229fa80 obj1;
    UnkStruct_0229fa80_2 obj2;
    u16 i;
    u16 idx;

    func_02062fbc(&obj1);
    func_02070c08(&obj2);

    i = 0x1323;
    while (i <= 0x1368u) {
        idx = i;
        func_02062ea4(&obj1, &idx);
        func_020a8bb8(&obj2, &obj1);
        if (func_020707e8(&obj2, param + 0x4248, param[0xa6]) != 0) {
            func_0206fc80((u8) (i - 0x1323));
            func_0206fc4c(1);
            func_02070be8(&obj2);
            func_02062f4c(&obj1);
            return;
        }
        i++;
    }

    func_0206fc4c(0);
    func_02070be8(&obj2);
    func_02062f4c(&obj1);
}
