/* func_ov068_0226d960 @ 0x0226d960, 0xc8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vt680 {
    u32 unk_00;
    u32 unk_04;
    void (*func8)(void *);
} Vt680;

typedef struct Obj680 {
    Vt680 *vt;
} Obj680;

extern int func_0202e364(void *);
extern void func_0201c280(void *, void *);
extern int func_02012550(void *, void *);
extern void func_ov068_0226d374(void *);
extern void func_ov068_0226d264(void *);

int func_ov068_0226d960(void *self)
{
    u16 val;
    unsigned int ok;

    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x680);
    ((Obj680 *) ((char *) self + 0x680))->vt->func8((char *) self + 0x680);

    *(u32 *) ((char *) self + 0x9f8) = 0;
    *(u32 *) ((char *) self + 0x9fc) = 0;
    *(u32 *) ((char *) self + 0xa0c) = 3;

    val = 0xfff1;
    ok = (func_02012550((char *) self + 0x9b4, &val) == 0);
    if (ok > 0) {
        return 0;
    }

    *(u32 *) ((char *) self + 0x628) = (u32) ((char *) self + 0x9b4);
    *(u32 *) ((char *) self + 0xa00) = (u32) -1;
    *(u8 *) ((char *) self + 0xa04) = 0;
    *(u8 *) ((char *) self + 0xa05) = 0;
    *(u16 *) ((char *) self + 0xa06) = 0;
    *(u8 *) ((char *) self + 0xa08) = 0xff;
    *(u8 *) ((char *) self + 0xa09) = 0;

    func_ov068_0226d374(self);
    func_ov068_0226d264(self);
    return 1;
}
