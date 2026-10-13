/* func_020a7dec @ 0x020a7dec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43f4;
extern void func_0208ffcc(void);
extern void func_0208ffc0(void);

void func_020a7dec(void)
{
    if (data_021f43f4 != 0) {
        func_0208ffcc();
    } else {
        func_0208ffc0();
    }
}
