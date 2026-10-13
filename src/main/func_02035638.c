/* func_02035638 @ 0x02035638, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035148(void *param1, void *param2, int param3);

extern unsigned char data_021c526c[];

void func_02035638(void *param)
{
    void *r0;
    void *r1;
    int r2;

    r1 = param;
    r0 = *(void **) data_021c526c;
    r2 = 0;
    func_02035148(r0, r1, r2);
}
