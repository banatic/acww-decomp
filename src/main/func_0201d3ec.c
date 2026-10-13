/* func_0201d3ec @ 0x0201d3ec, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201d3ec {
    int a;
    int b;
};
extern struct UnkStruct_0201d3ec data_020d8e60;
extern void func_020157c8(void *, int, int);
extern void func_02015828(void *, int);
extern void func_0202dbf0(void *, struct UnkStruct_0201d3ec);

int func_0201d3ec(void *param)
{
    func_020157c8(param, 0x32, 0);
    func_02015828(param, 2);
    func_0202dbf0(param, data_020d8e60);
    return 1;
}
