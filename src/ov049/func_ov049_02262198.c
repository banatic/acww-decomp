/* func_ov049_02262198 @ 0x02262198, 0x40 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c814c;
extern void func_0201ad18(void *p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7);
extern void func_ov049_02262a94(void *p0, int p1);

extern unsigned char data_021fbee8[];

void func_ov049_02262198(void *param)
{
    func_0201ad18((char *) param + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_ov049_02262a94(param, 1);
}
