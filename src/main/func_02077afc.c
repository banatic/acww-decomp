/* func_02077afc @ 0x02077afc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020e9968(void *a, void *b, void *c);

extern unsigned char data_021c9b30[];

void func_02077afc(void *a, void *b)
{
    void *r0;
    void *r1;
    void *r2;
    void *r3;

    r3 = a;
    r2 = b;
    r0 = *(void **) data_021c9b30;
    r1 = r3;
    r3 = (void *) 0x020e9968;
    func_020e9968(r0, r1, r2);
}
