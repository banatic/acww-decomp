/* func_020460ec @ 0x020460ec, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02046154(int *);
extern int func_02045c48(void);
extern void func_02046194(int, int, int *, int, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
                          signed char);

int func_020460ec(int a1, int *a2, int a3, int a4, unsigned char p5, unsigned char p6, unsigned char p7, unsigned char p8,
                  unsigned char p9, signed char p10)
{
    int local1[2];
    int local2[2];
    int result;
    int ret = 0;

    local1[0] = a2[0];
    local1[1] = a2[1];
    if (func_02046154(local1) == 0) {
        goto done;
    }

    result = func_02045c48();
    if (result < 0) {
        goto done;
    }

    local2[0] = a2[0];
    local2[1] = a2[1];
    func_02046194(result, a1, local2, a3, a4, p5, p6, p7, p8, p9, p10);
    ret = 1;

done:
    return ret;
}
