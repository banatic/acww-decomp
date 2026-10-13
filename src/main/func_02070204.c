/* func_02070204 @ 0x02070204, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e8ca8(void *arg, void *arg2);

extern unsigned char data_021cfca0[];

void func_02070204(void *arg)
{
    void *r1 = arg;
    void *r0 = (void *) data_021cfca0;
    void *r3 = (void *) 0x020e8ca8;
    func_020e8ca8(r0, r1);
}
