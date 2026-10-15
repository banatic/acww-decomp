/* func_ov004_0222ca34 @ 0x0222ca34, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222ca34 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual int v24(int);
};
extern "C" {
extern void func_02055124(void *object);
extern int func_02056f94(void *);
extern int func_0209d3f8(void *, int);
}

extern "C" void func_ov004_0222ca34(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02056f94(self + 0x188) != 0x0) {
        if (*(u8 *) (self + 0x374) == 0x0) {
            ((UnkStruct_0222ca34 *) self)->v24(0x2);
            return;
        }
        func_0209d3f8(self, 0x2);
    } else {
        func_02055124(self + 0xec);
    }
}
