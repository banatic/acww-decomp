/* func_020961e0 @ 0x020961e0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020963e4(void *param1, void *param2);

extern unsigned char data_021d5684[];

void func_020961e0(void *param1)
{
    void *r1;
    void *r0;
    void *r3;

    r1 = param1;
    r0 = (void *) data_021d5684;
    r3 = (void *) func_020963e4;
    func_020963e4(r0, r1);
}
