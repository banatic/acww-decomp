/* func_ov004_022347b8 @ 0x022347b8, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022347b8 {
    int a;
    ~UnkStruct_022347b8() {}
};

typedef struct {
    int m[12];
} Mtx;
extern "C" {
extern Mtx data_021fbe48;
extern void func_020e96c8(Mtx *, int, int, int);
extern void func_020e9744(Mtx *, int);
extern void func_020e9774(Mtx *, int);
}
extern "C" void func_ov004_022347b8(void *unused, char **pp)
{
    UnkStruct_022347b8 t;
    char *o = *pp;
    int *v = (int *) (o + 0x1a8);
    func_020e96c8(&data_021fbe48, v[0], v[1], v[2]);
    func_020e9744(&data_021fbe48, *(s16 *) (*pp + 0x1c0));
    func_020e9774(&data_021fbe48, *(s16 *) (*pp + 0x1c4));
    *(Mtx *) (o + 0xc8) = data_021fbe48;
}
