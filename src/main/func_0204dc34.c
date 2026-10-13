/* func_0204dc34 @ 0x0204dc34, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204dc34 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

extern struct UnkStruct_0204dc34 *func_0204f86c(int, int);
extern int func_0207cec0(int *, int);
extern int func_0207ffac(void);
extern void func_0204dbe4(int, int, int);
extern int data_021e5a2c;

struct UnkStruct_0204dc34 *func_0204dc34(int a, int b, int c)
{
    struct UnkStruct_0204dc34 *p;
    p = func_0204f86c(1, c);
    if (p) {
        if (func_0207cec0(&data_021e5a2c, b)) {
            p->unk_00 = func_0207ffac();
        } else {
            p->unk_00 = 0x1010;
        }
        func_0204dbe4(a, b, c);
        p->unk_04 = a;
        p->unk_08 = 0;
        p->unk_0C = 0;
    }
    return p;
}
