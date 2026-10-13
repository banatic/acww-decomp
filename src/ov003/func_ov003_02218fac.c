/* func_ov003_02218fac @ 0x02218fac, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00[3];
} UnkStruct_02218fac;
typedef struct {
    int pad_00[4];
} UnkStruct_02218fac_2;

extern void func_0200e92c(UnkStruct_02218fac *);
extern void func_0200e90c(UnkStruct_02218fac *, int, int, int);
extern void func_ov003_02218fec(UnkStruct_02218fac_2 *, int);
extern int func_0200e894(int, UnkStruct_02218fac *);
extern void func_0200e91c(UnkStruct_02218fac *);

int func_ov003_02218fac(int a, int b, int c, int d)
{
    UnkStruct_02218fac l1;
    UnkStruct_02218fac_2 l2;
    int result;

    func_0200e92c(&l1);
    func_0200e90c(&l1, 17, c, d);
    func_ov003_02218fec(&l2, b);
    result = func_0200e894(a, &l1);
    func_0200e91c(&l1);
    return result;
}
