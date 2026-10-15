/* func_0205b868 @ 0x0205b868, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c95f0;
extern void *data_021fbe94;
extern int func_0204daac(int b, void *data_021fbe94);
extern void func_0204da48(void *data_021fbe94);
struct UnkStruct_0205b868 {
    int x;
    int y;
};
extern void *func_0205bb48(struct UnkStruct_0205b868 *p);
extern void *func_0205bb30(struct UnkStruct_0205b868 *p);
extern void *func_0205b270(void *a, void *c, void *d, void *e, void *f, struct UnkStruct_0205b868 *p, int one, int b2,
                           int zero);

void *func_0205b868(void *a, int b, void *c, void *d, void *e, void *f)
{
    void *result;
    struct UnkStruct_0205b868 local;

    if (data_021c95f0 == 0) {
        data_021c95f0 = func_0204daac(b, data_021fbe94);
    }
    func_0205bb48(&local);
    result = func_0205b270(a, c, d, e, f, &local, 1, b, 0);
    if (data_021c95f0 != 0) {
        func_0204da48(data_021fbe94);
        data_021c95f0 = 0;
    }
    func_0205bb30(&local);
    return result;
}
