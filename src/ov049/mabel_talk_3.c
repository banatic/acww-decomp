/* mabel_talk_3: 4 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_02261a48 @ 0x02261a48, 0x22 bytes, Thumb
 * func_ov049_02261a24 @ 0x02261a24, 0x22 bytes, Thumb
 * func_ov049_02261a00 @ 0x02261a00, 0x22 bytes, Thumb
 * func_ov049_022619fc @ 0x022619fc, 0x2 bytes, Thumb
 */

extern void func_020157c8(void *param1, int param2, int param3);
extern int func_02015828(void *param1, int param2);
extern void func_ov049_022610c4(void *param1, int param2);

void func_ov049_02261a48(void *param1)
{
    func_020157c8(param1, 5, 0);
    func_02015828(param1, 2);
    func_ov049_022610c4(param1, 3);
}

void func_ov049_02261a24(int r0)
{
    func_020157c8((void *) r0, 7, 0);
    func_02015828((void *) r0, 2);
    func_ov049_022610c4((void *) r0, 4);
}

void func_ov049_02261a00(void *p)
{
    func_020157c8(p, 8, 0);
    func_02015828(p, 2);
    func_ov049_022610c4(p, 5);
}

void func_ov049_022619fc(void) {}
