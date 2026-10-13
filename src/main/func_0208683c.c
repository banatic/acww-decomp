/* func_0208683c @ 0x0208683c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02086874(void);
extern void func_0209df64(void *);

void func_0208683c(void *param)
{
    unsigned char a, b, c;
    void *sp;
    void *r4;

    r4 = param;
    func_02086874();
    func_0209df64(&sp);
    a = ((unsigned char *) &sp)[2];
    ((unsigned char *) r4)[0x46] = a;
    b = ((unsigned char *) &sp)[1];
    ((unsigned char *) r4)[0x45] = b;
    c = *(unsigned char *) &sp;
    ((unsigned char *) r4)[0x44] = c;
    ((unsigned char *) r4)[0x47] = 0;
}
