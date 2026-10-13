/* func_ov004_02231b58 @ 0x02231b58, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02231b58 {
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
    virtual int v18(int, void *);
};
extern "C" {
}

extern "C" int func_ov004_02231b58(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x4) + 0x2c) != 0x0) {
        return ((UnkStruct_02231b58 *) (char *) *(int *) ((char *) *(int *) (self + 0x4) + 0x2c))
            ->v18(*(u8 *) ((char *) *(int *) (self) + 0x1), self);
    }
    return *(int *) ((char *) *(int *) (self + 0x4) + 0x2c);
}
