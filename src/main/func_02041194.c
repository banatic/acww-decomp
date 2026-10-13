/* func_02041194 @ 0x02041194, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);
extern int func_0209dcdc(void *, void *);
extern void func_02040c90(void *, int);
extern void func_0203fe58(int);
extern void func_02041788(void);

void func_02041194(void *self)
{
    unsigned char local1[4], local2[4];

    func_0209df64(local1);
    if (func_0209dcdc(local1, (unsigned char *) self + 8) >= 7) {
        ((unsigned char *) self)[8] = 1;
        ((unsigned char *) self)[9] = 1;
        ((unsigned char *) self)[10] = 0;
        ((unsigned char *) self)[11] = 0;
    }

    func_0209df64(local2);
    if (func_0209dcdc(local2, (unsigned char *) self + 12) >= 7) {
        ((unsigned char *) self)[12] = 1;
        ((unsigned char *) self)[13] = 1;
        ((unsigned char *) self)[14] = 0;
        ((unsigned char *) self)[15] = 0;
    }

    func_02040c90(self, 0);
    func_0203fe58(1);
    func_02041788();
}
