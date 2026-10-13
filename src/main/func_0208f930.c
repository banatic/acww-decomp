/* func_0208f930 @ 0x0208f930, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001cf4(int);
extern void func_02001bb4(int);

extern unsigned char data_021d3654[];
extern unsigned char data_021d3674[];

void func_0208f930(void)
{
    unsigned int *ptr;
    unsigned char *byte_ptr;

    ptr = (unsigned int *) data_021d3654;
    if (ptr[8] != 0) {
        func_02001cf4(0x10);
        func_02001bb4(4);
    }
    byte_ptr = (unsigned char *) data_021d3674;
    byte_ptr[0x19] = 0;
}
