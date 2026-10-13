/* func_02076ac0 @ 0x02076ac0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(void *param1, void *param2, int param3);
extern void func_0209d4c0(void *param1, void *param2);
extern void *data_020ccf94;

void func_02076ac0(void *param1, void *param2, void *param3, void *param4)
{
    void *sp0;
    void *r4 = param4;
    func_020736bc(data_020ccf94, &sp0, 1);
    func_0209d4c0(&sp0, r4);
}
