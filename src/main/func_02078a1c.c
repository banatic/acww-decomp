/* func_02078a1c @ 0x02078a1c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned long func_02078b64(void *param1, void *param2);

extern unsigned char data_021d12a4[];

unsigned long func_02078a1c(void *param)
{
    void *r1;
    void *r0;
    void *r3;

    r1 = param;
    r0 = (void *) data_021d12a4;
    r1 = *(void **) r1;
    r3 = (void *) func_02078b64;
    return func_02078b64(r0, r1);
}
