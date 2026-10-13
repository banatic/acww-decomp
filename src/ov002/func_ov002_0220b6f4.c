/* func_ov002_0220b6f4 @ 0x0220b6f4, 0x28 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(int which);
extern void func_02068484(void *p, void *q, int x);
extern void func_02068428(void *p);
extern void func_02068434(void *p);

extern char data_021f43e8;

void func_ov002_0220b6f4(void)
{
    void *p = func_020682e0(1);

    func_02068484(p, &data_021f43e8, 0);
    func_02068428(p);
    func_02068434(p);
}
