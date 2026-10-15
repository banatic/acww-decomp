/* func_02045aa4 @ 0x02045aa4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02045aa4 {
    int a;
    int b;
};

struct UnkStruct_02045aa4_2 {
    int a;
    int b;
};

extern int func_02044878(int arg);
extern int func_02045ac4(struct UnkStruct_02045aa4_2 *local, int val);

int func_02045aa4(struct UnkStruct_02045aa4 *src, int arg)
{
    struct UnkStruct_02045aa4_2 local;
    int val;
    local.a = src->a;
    local.b = src->b;
    val = func_02044878(arg);
    return func_02045ac4(&local, val);
}
