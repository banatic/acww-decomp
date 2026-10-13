/* func_ov003_02211980 @ 0x02211980, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);
extern void func_ov003_022119d8(void *, void *, int, int);

int func_ov003_02211980(void *a, void *b, int c, int d, short e)
{
    char local[12];
    char local2[16];
    int local3[3];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x5f, d, e);
    local3[0] = ((int *) b)[0];
    local3[1] = ((int *) b)[1];
    local3[2] = ((int *) b)[2];
    func_ov003_022119d8(local2, local3, 0xfff1, c);
    result = func_0200e894(a, local);
    func_0200e91c(local);
    return result;
}
