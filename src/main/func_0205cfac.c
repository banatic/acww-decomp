/* func_0205cfac @ 0x0205cfac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0205d0c8(void *param1, unsigned char param2);

extern unsigned char data_021c9c2c[];

void func_0205cfac(unsigned char *param0)
{
    unsigned char value;
    void *global_ptr;

    value = *param0;
    global_ptr = (void *) data_021c9c2c;
    func_0205d0c8(global_ptr, value);
}
