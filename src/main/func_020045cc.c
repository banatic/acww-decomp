/* func_020045cc @ 0x020045cc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f1ecc(void *param1, void *param2);

extern unsigned char data_021fd1bc[];

void func_020045cc(void *param1)
{
    void *r0 = (void *) data_021fd1bc;
    void *r1 = param1;
    func_020f1ecc(r0, r1);
}
