/* func_0208f8fc @ 0x0208f8fc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001cf4(int);
extern void func_02001d1c(int);
extern void func_02001bb4(int);

extern unsigned char data_021d3654[];
extern unsigned char data_021d3674[];

void func_0208f8fc(void)
{
    unsigned int *p;
    unsigned char *q;

    p = (unsigned int *) data_021d3654;
    if (p[8] != 0) {
        func_02001cf4(0x10);
        func_02001d1c(4);
        func_02001bb4(4);
    }
    q = (unsigned char *) data_021d3674;
    q[0x19] = 0;
}
