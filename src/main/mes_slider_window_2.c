/* mes_slider_window_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020abbcc @ 0x020abbcc, 0x2c bytes, Thumb
 * func_020abbb8 @ 0x020abbb8, 0x14 bytes, Thumb
 * func_020abb8c @ 0x020abb8c, 0x2c bytes, Thumb
 * func_020abb78 @ 0x020abb78, 0x14 bytes, Thumb
 * func_020abb5c @ 0x020abb5c, 0x1c bytes, Thumb
 * func_020abb48 @ 0x020abb48, 0x14 bytes, Thumb
 * func_020abb2c @ 0x020abb2c, 0x1a bytes, Thumb
 * func_020abb08 @ 0x020abb08, 0x24 bytes, Thumb
 * func_020abaec @ 0x020abaec, 0x1a bytes, Thumb
 */

extern void func_020aba5c(unsigned char *);
extern void func_020abc6c(int, int);
extern int func_0208e484(void *);
extern void func_0200467c(int);
extern void func_020aca30(int *ptr);
extern void func_020aca24(void *);
extern int func_020aca54(void *ptr);
extern void func_020aca48(void *);
extern void func_020abbf8(void *ptr);

void func_020abbb8(int p0);
void func_020abb78(int *obj);
void func_020abb48(void *obj);
void func_020abb08(void *arg0);

void func_020abbcc(unsigned char *arg0)
{
    if (arg0[0x141] != 0) {
        func_020abbb8((int) arg0);
    } else if (arg0[0x143] != 0) {
        func_020aba5c(arg0);
    }
}

void func_020abbb8(int p0)
{
    *(int *) ((char *) (p0) + (316)) = 2;
    func_020abc6c(p0, 2);
}

void func_020abb8c(void *param)
{
    void *r4;
    r4 = param;
    if (func_0208e484((char *) param + 0x20)) {
        if (((unsigned char *) r4)[0x145]) {
            func_0200467c(0x33);
        }
        func_020abb78((int *) r4);
    }
}

void func_020abb78(int *obj)
{
    obj[0x4f] = 3;
    func_020aca30(&obj[0x39]);
}

void func_020abb5c(void *param)
{
    unsigned char val;
    unsigned char *ptr;

    val = ((unsigned char *) param)[0x141];
    if (val == 0) {
        func_020abb48(param);
    }
}

void func_020abb48(void *obj)
{
    *(unsigned int *) ((char *) obj + 0x13c) = 4;
    func_020aca24((char *) obj + 0xe4);
}

void func_020abb2c(void *ptr)
{
    if (func_020aca54((char *) ptr + 0xe4)) {
        func_020abb08(ptr);
    }
}

void func_020abb08(void *arg0)
{
    *(int *) ((char *) arg0 + 0x13c) = 5;
    func_020aca48((char *) arg0 + 0xe4);
    func_020abc6c((int) arg0, 3);
}

void func_020abaec(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x20)) {
        func_020abbf8(ptr);
    }
}
