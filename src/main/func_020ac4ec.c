/* func_020ac4ec @ 0x020ac4ec, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac478(void *param1, int param2, int param3);
extern void func_020ac470(void *param1, int param2);

void func_020ac4ec(void *param1)
{
    func_020ac478(param1, 9, 0x14);
    func_020ac470(param1, 9);
    *(unsigned short *) ((char *) param1 + 0x1e) = 5;
}
