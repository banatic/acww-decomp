/* func_0202d994 @ 0x0202d994, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202d994;
typedef void (UnkStruct_0202d994::*PMF)(int);
struct UnkStruct_0202d994 {
    unsigned char pad_00[0xb0];
    PMF pmf;
};
extern "C" void func_0202d994(UnkStruct_0202d994 *p, int a);
void func_0202d994(UnkStruct_0202d994 *p, int a)
{
    if (p->pmf) {
        (p->*(p->pmf))(a);
    }
}
