/* func_ov143_02299b04 @ 0x02299b04, 0x28 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_02299630(void *p, int a);
extern void func_ov143_0229a2e0(void *p);
extern void func_ov143_02299ba0(void *p, int a);

struct UnkStruct_02299b04 {
    char pad_00[0x9a];
    short unk_9A;
};

void func_ov143_02299b04(struct UnkStruct_02299b04 *p)
{
    func_ov143_02299630(p, 2);
    p->unk_9A = -1;
    func_ov143_0229a2e0(p);
    func_ov143_02299ba0(p, 3);
}
