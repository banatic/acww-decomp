/* outdoor_villager_object_3: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226da64 @ 0x0226da64, 0x58 bytes, Thumb
 * func_ov068_0226da28 @ 0x0226da28, 0x3c bytes, Thumb
 * func_ov068_0226d960 @ 0x0226d960, 0xc8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x830];
    void *unk_830;
} UnkStruct_0226da28;

typedef struct Vt680 {
    u32 unk_00;
    u32 unk_04;
    void (*func8)(void *);
} Vt680;

typedef struct Obj680 {
    Vt680 *vt;
} Obj680;

extern void *func_020edf70(int size);
extern void *func_0202e8e4(void *p);
extern void func_ov068_02266cf0(void *p);
extern void *func_ov068_0226ce5c(void *p);
extern void *func_0201259c(void *p);
extern void func_ov068_02266f40(void *p);
extern char data_ov068_022771c0;
extern int func_0207f270(void *p);
extern int func_02079544(int v);
extern int func_0202e364(void *);
extern void func_0201c280(void *, void *);
extern int func_02012550(void *, void *);
extern void func_ov068_0226d374(void *);
extern void func_ov068_0226d264(void *);

void *func_ov068_0226da64(void)
{
    void *p;
    p = func_020edf70(0xa10);
    if (p != 0) {
        func_0202e8e4(p);
        *(void **) p = (void *) &data_ov068_022771c0;
        func_ov068_02266cf0((char *) p + 0x898);
        func_ov068_0226ce5c((char *) p + 0x8b8);
        func_0201259c((char *) p + 0x9b4);
        func_ov068_02266f40((char *) p + 0x9f4);
    }
    return p;
}

int func_ov068_0226da28(UnkStruct_0226da28 *p)
{
    int r6 = 0;
    int r4 = r6;
    if (p->unk_830 != 0 && func_0207f270(p->unk_830) != 0) {
        r4 = 1;
    }
    if (r4 != 0 && func_02079544(func_0207f270(p->unk_830)) == 1) {
        r6 = 1;
    }
    return r6;
}

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
