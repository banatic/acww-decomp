/* func_0207acf8 @ 0x0207acf8, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0207acf8 {
    char pad_00[0x7ec];
};

extern int func_020951bc(int b);
extern int func_0208150c(struct UnkStruct_0207acf8 *p);
extern int func_02003704(int v);
extern int func_0207f270(struct UnkStruct_0207acf8 *p);
extern int func_020794d8(int v);
extern int func_020807a8(struct UnkStruct_0207acf8 *p, int b);
extern struct UnkStruct_0207acf8 *func_0207cc54(int mask, int count, int total);
extern int func_0207cf74(unsigned int);
extern int func_0207f150(struct UnkStruct_0207acf8 *p);
extern int func_0207b3dc(struct UnkStruct_0207acf8 *a);
extern struct UnkStruct_0207acf8 *func_0207cec0(struct UnkStruct_0207acf8 *a, struct UnkStruct_0207acf8 *res);
extern void func_02081888(unsigned short *);

void func_0207acf8(struct UnkStruct_0207acf8 *a, int b)
{
    unsigned short *condition_value0;
    u8 mask;
    int count;
    struct UnkStruct_0207acf8 *p;
    int i;
    struct UnkStruct_0207acf8 *res;

    if (func_020951bc(b) != 0) {
        p = a;
        mask = 0;
        count = 0;
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c(p)) != 0) {
                if (func_020794d8(func_0207f270(p)) == 0) {
                    if (func_020807a8(p, b) != 0) {
                        mask = (u8) (mask | (1 << i));
                        count++;
                    }
                }
            }
            p++;
        }
        res = func_0207cc54(mask, count, 8);
        if (func_0207cf74((unsigned int) res) == 0) {
            mask = 0;
            count = 0;
            p = a;
            for (i = 0; i < 8; i++) {
                if (func_02003704(func_0208150c(p)) != 0) {
                    if (func_0207f150(p) == 3) {
                        if (i != func_0207b3dc(a)) {
                            if (func_020807a8(p, b) != 0) {
                                mask = (u8) (mask | (1 << i));
                                count++;
                            }
                        }
                    }
                }
                p++;
            }
            res = func_0207cc54(mask, count, 8);
        }
        res = func_0207cec0(a, res);
        if (res != 0) {
            if (func_02003704(func_0208150c(res)) != 0) {
                if ((condition_value0 = (unsigned short *) (func_020807a8(res, b))) != 0) {
                    func_02081888(condition_value0);
                }
            }
        }
    }
}