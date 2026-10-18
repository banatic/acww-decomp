/* func_ov068_02274358 @ 0x02274358, 0x94 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 * compiler-emitted symbol: _ZN18Obj_ov068_02277dc019func_ov068_02274358EPv
 */

#include "cpp/ov068/Obj_ov068_02277dc0.h"

// Member-function pointer constants the ROM keeps with other users' in .data:
// &func_ov068_02274334, &func_ov068_02274314, &func_ov068_02274314.
extern void (Obj_ov068_02277dc0::*data_ov068_022779fc)();
extern void (Obj_ov068_02277dc0::*data_ov068_02277a04)();
extern void (Obj_ov068_02277dc0::*data_ov068_02277a6c)();

// The argument of the slot that calls this is handed on but never read.
void Obj_ov068_02277dc0::func_ov068_02274358(void *arg)
{
    static struct Entry {
        unsigned int key;
        void (Obj_ov068_02277dc0::*pmf)();
    } tbl[3] = {{0x07, data_ov068_022779fc}, {0x06, data_ov068_02277a04}, {0x09, data_ov068_02277a6c}};
    unsigned int i;
    unsigned char *bytePtr;
    for (i = 0, bytePtr = (unsigned char *) this + 0x1e; i < 3; i++) {
        unsigned int k = tbl[i].key;
        if (k == *bytePtr) {
            (this->*tbl[i].pmf)();
        }
    }
}
