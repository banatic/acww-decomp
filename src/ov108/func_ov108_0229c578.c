/* func_ov108_0229c578 @ 0x0229c578, 0x3c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(int, int);
extern void func_ov002_0220a374(int, int);
extern void func_ov002_02208098(int, int);

void func_ov108_0229c578(int *param1, unsigned char param2)
{
    func_ov002_02207d24((int) ((char *) param1 + 0x23b0), 1);
    *(unsigned char *) ((char *) param1 + 0x2b2) = param2;
    func_ov002_0220a374((int) ((char *) param1 + 0x2498), 5);
    func_ov002_02208098((int) param1, 0xf);
}
