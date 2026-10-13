/* func_ov140_0229a73c @ 0x0229a73c, 0x38 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_02299fa0(int param1, int param2);
extern void func_ov002_02208090(int param1, int param2);
extern void func_ov002_02208098(int param1, int param2);
extern void RtcSendPxiCommand(int param1);

void func_ov140_0229a73c(int param1)
{
    int *ptr;
    int value;

    func_ov140_02299fa0(param1, 2);
    ptr = (int *) (param1 + 0xa4);
    *ptr = 10;
    *(char *) (param1 + 0x8db) = 5;
    func_ov002_02208090(param1, 3);
    func_ov002_02208098(param1, 5);
    RtcSendPxiCommand(0x28);
}
