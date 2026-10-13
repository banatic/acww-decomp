/* func_0203a970 @ 0x0203a970, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203a958(void *p, int a, int b, int c, int d);

extern unsigned char data_020da70c[];

void *func_0203a970(void *p)
{
    *((unsigned int *) p) = (unsigned int) data_020da70c;
    func_0203a958(p, 0x00001555, 0x00000e38, 0x00001000, 0x01388000);
    return p;
}
