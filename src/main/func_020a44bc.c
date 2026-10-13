/* func_020a44bc @ 0x020a44bc, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(int);
extern void func_02068320(void *p, int val);
extern void func_020a53ec(int, int, int, int);
extern void func_020a4e94(void *param, int val);

void func_020a44bc(void *param)
{
    struct UnkStruct_020a44bc {
        int pad_00;
        int field;
    } *p;
    int zero;

    p = func_020682e0(0);
    if (p->field != 0) {
        return;
    }
    zero = 0;
    func_02068320(p, p->field);
    func_020a53ec(2, 3, zero, zero);
    func_020a4e94(param, 0);
}
