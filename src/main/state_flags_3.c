/* state_flags_3: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f7a4 @ 0x0206f7a4, 0xc bytes, Thumb
 * func_0206f798 @ 0x0206f798, 0xc bytes, Thumb
 * func_0206f78c @ 0x0206f78c, 0xc bytes, Thumb
 * func_0206f780 @ 0x0206f780, 0xc bytes, Thumb
 * func_0206f774 @ 0x0206f774, 0xc bytes, Thumb
 * func_0206f768 @ 0x0206f768, 0xc bytes, Thumb
 * func_0206f74c @ 0x0206f74c, 0x1c bytes, Thumb
 */

extern int func_0206fec8(int arg);
extern void func_0206fef0(int);
extern void func_0206fee0(int);

int func_0206f7a4(void)
{
    return func_0206fec8(8);
}

int func_0206f798(void)
{
    return func_0206fec8(0x20);
}

int func_0206f78c(void)
{
    return func_0206fec8(0x40);
}

void func_0206f780(void)
{
    func_0206fef0(8);
}

void func_0206f774(void)
{
    func_0206fef0(0x20);
}

void func_0206f768(void)
{
    func_0206fef0(0x40);
}

void func_0206f74c(void)
{
    func_0206fee0(8);
    func_0206fee0(0x20);
    func_0206fee0(0x40);
}
