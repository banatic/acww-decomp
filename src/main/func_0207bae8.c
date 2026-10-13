/* func_0207bae8 @ 0x0207bae8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073d90(unsigned int);
extern int func_0207cf14(int, int);
extern void func_02079bc4(int, int, int, int);

void func_0207bae8(int p1, int p2, int p3, int p4)
{
    int v1, v2;
    if (func_02073d90(data_020ccf94)) {
        return;
    }
    v1 = func_0207cf14(p1, p2);
    v2 = func_0207cf14(p1, p3);
    func_02079bc4(p1 + 0x3f60, v1, v2, p4);
}
