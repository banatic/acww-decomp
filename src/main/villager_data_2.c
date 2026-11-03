/* villager_data_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208090c @ 0x0208090c, 0x1c bytes, Thumb
 * func_020808ec @ 0x020808ec, 0x20 bytes, Thumb
 */

extern int func_02080a2c(unsigned int object);
extern int func_02082264(int);
extern unsigned int func_0208150c(unsigned int);
extern int func_02003648(unsigned char *);
extern int func_02082500(int);

int func_0208090c(unsigned int object)
{
    int r0;
    int r1;

    r0 = func_02080a2c(object);
    r1 = 0xc;
    if (r0 != 0) {
        r1 = func_02082264(r0);
    }
    return r1;
}

int func_020808ec(unsigned int object)
{
    int r4;
    int r0;

    r4 = 0x21;
    r0 = func_02082500((int) func_02003648((unsigned char *) func_0208150c(object)));
    if (r0 != 0) {
        r0 += 0x4c;
        r4 = *(unsigned char *) r0;
    }
    return r4;
}
