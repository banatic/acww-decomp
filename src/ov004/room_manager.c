/* room_manager: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223b314 @ 0x0223b314, 0x20 bytes, Thumb
 * func_ov004_0223b2ec @ 0x0223b2ec, 0x28 bytes, Thumb
 * func_ov004_0223b2cc @ 0x0223b2cc, 0x20 bytes, Thumb
 * func_ov004_0223b2ac @ 0x0223b2ac, 0x20 bytes, Thumb
 * func_ov004_0223b28c @ 0x0223b28c, 0x20 bytes, Thumb
 * func_ov004_0223b274 @ 0x0223b274, 0x18 bytes, Thumb
 * func_ov004_0223b258 @ 0x0223b258, 0x1c bytes, Thumb
 */

#include "types.h"

extern void *data_ov004_022595c0;
extern int func_ov004_0223a7cc(void *p);
extern int func_ov004_0223a7f0(void *);
extern int func_ov004_0223a7c0(void *p);
extern int func_ov004_0223a7a8(void *p);
extern int func_ov004_0223a790(void *p);

int func_ov004_0223b314(void)
{
    void *p = data_ov004_022595c0;
    if (p != 0) {
        return func_ov004_0223a7cc((char *) p + 0x64);
    }
    return 0;
}

short func_ov004_0223b2ec(void)
{
    if (data_ov004_022595c0 != 0) {
        return (short) func_ov004_0223a7f0((char *) data_ov004_022595c0 + 0x64);
    }
    return -1;
}

int func_ov004_0223b2cc(void)
{
    void *p = data_ov004_022595c0;
    if (p != 0) {
        return func_ov004_0223a7c0((char *) p + 0x64);
    }
    return 0;
}

int func_ov004_0223b2ac(void)
{
    void *p = data_ov004_022595c0;
    if (p != 0) {
        return func_ov004_0223a7a8((char *) p + 0x64);
    }
    return 0xff;
}

int func_ov004_0223b28c(void)
{
    void *p = data_ov004_022595c0;
    if (p != 0) {
        return func_ov004_0223a790((char *) p + 0x64);
    }
    return 0;
}

void func_ov004_0223b274(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022595c0) != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_022595c0) + 0x2b0) = 0x1;
    }
}

int func_ov004_0223b258(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022595c0) != 0x0) {
        return *(u8 *) ((char *) *(int *) ((char *) &data_ov004_022595c0) + 0x2b0);
    }
    return 0x0;
}
