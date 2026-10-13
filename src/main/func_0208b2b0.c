/* func_0208b2b0 @ 0x0208b2b0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02011f48(int a, int b);
extern void func_02011f74(int a, int b);

struct UnkStruct_0208b2b0 {
    int unk_00;
    int unk_04;
};

void func_0208b2b0(struct UnkStruct_0208b2b0 *p)
{
    p->unk_04 = 2;
    func_02011f48(1, 2);
    func_02011f74(1, 1);
}
