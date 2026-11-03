/* room_object_light: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220ee88 @ 0x0220ee88, 0x8 bytes, Thumb
 * func_ov004_0220ee74 @ 0x0220ee74, 0x12 bytes, Thumb
 */

extern int func_020b67e8(unsigned int parameter0);
extern int func_020b65c4(void);

int func_ov004_0220ee88(unsigned int arg0)
{
    return func_020b67e8(arg0);
}

int func_ov004_0220ee74(void)
{
    // DECLS
    // ENDDECLS
    return func_ov004_0220ee88(func_020b65c4());
}
