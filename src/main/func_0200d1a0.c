/* func_0200d1a0 @ 0x0200d1a0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[12];
} UnkStruct_0200d1a0;

typedef struct {
    char data[16];
} UnkStruct_0200d1a0_2;

extern unsigned int func_0200e92c(UnkStruct_0200d1a0 *);
extern void func_0200e90c(UnkStruct_0200d1a0 *, int, int, int);
extern void func_0200d1e0(UnkStruct_0200d1a0_2 *, int);
extern int func_0200e894(int, UnkStruct_0200d1a0 *);
extern int func_0200e91c(UnkStruct_0200d1a0 *);

int func_0200d1a0(int p0, int p1, int p2, int p3)
{
    UnkStruct_0200d1a0 v1;
    UnkStruct_0200d1a0_2 v2;
    int result;

    func_0200e92c(&v1);
    func_0200e90c(&v1, 3, p2, p3);
    func_0200d1e0(&v2, p1);
    result = func_0200e894(p0, &v1);
    func_0200e91c(&v1);
    return result;
}
