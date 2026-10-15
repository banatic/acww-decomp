/* func_0209e380 @ 0x0209e380, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209dcdc(void *a, void *b);

int func_0209e380(void *r0, void *r1)
{
    unsigned char sp[8];
    unsigned char *p = sp;

    sp[2] = ((unsigned char *) r1)[5];
    sp[1] = ((unsigned char *) r1)[4];
    sp[0] = ((unsigned char *) r1)[3];
    sp[6] = ((unsigned char *) r0)[5];
    sp[5] = ((unsigned char *) r0)[4];
    sp[4] = ((unsigned char *) r0)[3];

    return func_0209dcdc(sp, sp + 4);
}
