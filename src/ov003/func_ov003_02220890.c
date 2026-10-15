/* func_ov003_02220890 @ 0x02220890, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern void func_ov003_02220138(void);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_02239b2c[];

void *func_ov003_02220890(void *arg0)
{
    func_020ee660(arg0);
    *(void **) arg0 = (void *) data_020da13c;
    *(void **) arg0 = (void *) data_ov003_02239b2c;
    func_ov003_02220138();
    return arg0;
}
