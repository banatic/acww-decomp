/* pool_link: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082c5c @ 0x02082c5c, 0x3a bytes, Thumb
 * func_02082c54 @ 0x02082c54, 0x8 bytes, Thumb
 * func_02082c4c @ 0x02082c4c, 0x8 bytes, Thumb
 * func_02082c44 @ 0x02082c44, 0x8 bytes, Thumb
 * func_02082c3c @ 0x02082c3c, 0x8 bytes, Thumb
 * func_02082c34 @ 0x02082c34, 0x8 bytes, Thumb
 * func_02082c2c @ 0x02082c2c, 0x8 bytes, Thumb
 * func_02082c24 @ 0x02082c24, 0x8 bytes, Thumb
 * func_02082c1c @ 0x02082c1c, 0x8 bytes, Thumb
 * func_02082c14 @ 0x02082c14, 0x8 bytes, Thumb
 * func_02082c0c @ 0x02082c0c, 0x8 bytes, Thumb
 */

extern int func_02083b00(void);
extern void func_02083c50(void *);
extern int func_02083708(void);
extern int func_020835a0(void);
extern int func_02083460(void);
extern int func_02083320(void);
extern int func_020831c0(void);
extern int func_0208385c(void);
extern int func_0208399c(void);

void func_02082c5c(void)
{
    func_02083c50((void *) func_02083b00());
    func_02083c50((void *) func_02083708());
    func_02083c50((void *) func_020835a0());
    func_02083c50((void *) func_02083460());
    func_02083c50((void *) func_02083320());
    func_02083c50((void *) func_020831c0());
}

void func_02082c54(void)
{
    func_02082c5c();
}

void func_02082c4c(void)
{
    func_02082c5c();
}

void func_02082c44(void)
{
    func_020831c0();
}

void func_02082c3c(void)
{
    func_02083320();
}

void func_02082c34(void)
{
    func_02083460();
}

void func_02082c2c(void)
{
    func_020835a0();
}

void func_02082c24(void)
{
    func_02083708();
}

void func_02082c1c(void)
{
    func_0208385c();
}

void func_02082c14(void)
{
    func_0208399c();
}

void func_02082c0c(void)
{
    func_02083b00();
}
