/* func_02008690 @ 0x02008690, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02008738(void *param1, void *param2);
extern int func_02008750(void *param1, void *param2, int param3, void *param4);

void func_02008690(void *param1, void *param2)
{
    unsigned short local[2];
    void *sp;

    func_02008738((char *) param1 + 0x8f0, &local[0]);
    local[1] = local[0];
    func_02008750(param1, &local[1], 6, param2);
}
