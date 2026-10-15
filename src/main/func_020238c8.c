/* func_020238c8 @ 0x020238c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207b410(unsigned int address);
extern void *func_0209a778(void *record);
extern int func_0209bd44(void *);
extern void func_0209bb90(int, int);

extern unsigned char data_021e5a2c[];

void func_020238c8(void)
{
    void *record = func_0209a778((void *) func_0207b410((unsigned int) data_021e5a2c));
    if (func_0209bd44(record) != 0) {
        func_0209bb90((int) record, 1);
    }
}
