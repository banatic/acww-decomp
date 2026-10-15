/* func_ov004_0223c758 @ 0x0223c758, 0x5e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long x, y, z;
} UnkStruct_0223c758;
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *, long);
extern int func_ov004_0220fd8c(char *self);
extern void func_ov004_0223cb60(void *, long, UnkStruct_0223c758 *, UnkStruct_0223c758 *, long, UnkStruct_0223c758 *,
                                UnkStruct_0223c758 *, short, long);
int func_ov004_0223c758(char *p0, long id, UnkStruct_0223c758 *b, UnkStruct_0223c758 *c, long e, UnkStruct_0223c758 *f,
                        UnkStruct_0223c758 *g, short h, long i)
{
    void *selected;
    if (id != -1) {
        if ((selected = func_ov004_0223cd58(func_ov004_0223ce84(), id)) != 0) {
            func_ov004_0223cb60(p0 + ((func_ov004_0220fd8c((char *) selected) & 1) << 6), id, b, c, e, f, g, h, i);
            return 1;
        }
        return 0;
    }
    return 0;
}
