/* func_0202e5e0 @ 0x0202e5e0, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020d9e88;
extern void *data_020d8c64;
extern void *data_020d8414;

extern void func_0201cdbc(void *);
extern void func_02082fbc(void *);
extern void func_0202de84(void *);
extern void func_0202e094(void *);
extern void func_02014898(void *);
extern void func_02019eac(void *);
extern void func_02013c28(void *);
extern void func_020f5914(void *);
extern void func_02089c70(void *);
extern void func_02032c50(void *);
extern void func_0201a790(void *);
extern void func_0201a7e8(void *);
extern void func_0201ade4(void *);
extern void func_0201b320(void *);
extern void func_02016998(void *);
extern void func_0201a3f8(void *);
extern void func_0201b390(void *);
extern void func_02054630(void *);
extern void func_0203f080(void *);

void *func_0202e5e0(u8 *p)
{
    *(void **) p = &data_020d9e88;
    func_0201cdbc(p + 0x83c);
    func_02082fbc(p + 0x828);
    func_0202de84(p + 0x680);
    func_0202e094(p + 0x64c);
    *(void **) p = &data_020d8c64;
    func_02014898(p + 0x618);
    func_02019eac(p + 0x564);
    func_02013c28(p + 0x558);
    *(void **) (p + 0x514) = &data_020d8414;
    func_020f5914(p + 0x514);
    func_02089c70(p + 0x4cc);
    func_02032c50(p + 0x49c);
    func_0201a790(p + 0x420);
    func_0201a7e8(p + 0x418);
    func_0201ade4(p + 0x3b0);
    func_0201b320(p + 0x350);
    func_02016998(p + 0x334);
    func_0201a3f8(p + 0x2ac);
    func_0201b390(p + 0x2a0);
    func_02054630(p + 0xec);
    func_0203f080(p);
    return p;
}
