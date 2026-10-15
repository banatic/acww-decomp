/* func_020b6dcc @ 0x020b6dcc, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020b6dcc {
    u8 pad_00[4];
    u8 flag;
};

extern struct UnkStruct_020b6dcc *data_021f6948;
extern void *data_021fbe94;

extern int func_0203750c(void);
extern int func_020379bc(int, int);
extern void *func_02053e5c(int);
extern void func_02062ae4(int);
extern int func_02072614(void);
extern void func_020726b8(void *);
extern void func_0205cf84(void *);
extern void func_0205d724(void *);
extern void func_0205dd98(void *);
extern void func_0205db10(void *);
extern void func_0205dc58(void *);
extern void func_0205f820(void *);
extern void func_0205d234(void *);
extern void func_0205e8b0(void *);
extern void func_0205f9ac(void *);
extern void func_0205e0f0(void *);
extern void func_0205f6f8(void *);
extern void func_0206094c(void *);
extern void func_020ad4fc(int);
extern int func_020ace54(void);
extern void func_02078da4(void);
extern void func_02082c54(void);
extern void func_020826d0(void);
extern void func_0205c1a4(void *);
extern void func_0209d51c(void);
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern void func_020b5e90(void);
extern void func_020ad74c(void);

int func_020b6dcc(void)
{
    func_020379bc(func_0203750c(), data_021f6948->flag == 1);
    func_02053e5c(data_021f6948->flag == 1);
    func_02062ae4(data_021f6948->flag == 1);
    func_020726b8((void *) func_02072614());
    func_0205cf84(data_021fbe94);
    func_0205d724(data_021fbe94);
    func_0205dd98(data_021fbe94);
    func_0205db10(data_021fbe94);
    func_0205dc58(data_021fbe94);
    func_0205f820(data_021fbe94);
    func_0205d234(data_021fbe94);
    func_0205e8b0(data_021fbe94);
    func_0205f9ac(data_021fbe94);
    func_0205e0f0(data_021fbe94);
    func_0205f6f8(data_021fbe94);
    func_0206094c(data_021fbe94);
    func_020ad4fc(data_021f6948->flag == 1);
    func_020ace54();
    func_02078da4();
    func_02082c54();
    func_020826d0();
    func_0205c1a4(data_021fbe94);
    func_0209d51c();
    if (func_020b65c4() == 0x2c || func_020b65c4() == 0x2d) {
        func_020b5e10();
        func_020b5e90();
    }
    func_020ad74c();
    return 1;
}
