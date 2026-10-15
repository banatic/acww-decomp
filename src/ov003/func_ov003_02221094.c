/* func_ov003_02221094 @ 0x02221094, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0223cfe4;
extern int func_ov003_022213f8(void *, int, void *, void *, int, int, int, int);

struct UnkStruct_02221094 {
    int a;
    int b;
};
struct UnkStruct_02221094_2 {
    int a;
    int b;
    int c;
};

void func_ov003_02221094(int a0, int a1, struct UnkStruct_02221094 *p2, struct UnkStruct_02221094_2 *p3, int a4)
{
    struct UnkStruct_02221094_2 local3;
    struct UnkStruct_02221094 local2;

    local3.a = p3->a;
    local3.b = p3->b;
    local3.c = p3->c;
    local2.a = p2->a;
    local2.b = p2->b;

    func_ov003_022213f8(&data_ov003_0223cfe4, a0, &local2, &local3, 6, a1, 0, a4);
}
