/* func_ov003_022240cc @ 0x022240cc, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    u8 unk_0C;
} UnkStruct_022240cc;
extern void ****data_ov003_02239f68[];
void *func_ov003_022240cc(UnkStruct_022240cc *o)
{
    void ****a;
    void ***b;
    void **c;
    void *r = 0;
    a = data_ov003_02239f68[o->unk_00];
    if (a != 0) {
        b = a[o->unk_08];
        if (b != 0) {
            c = b[o->unk_0C];
            if (c != 0) {
                r = c[o->unk_04];
            }
        }
    }
    return r;
}
