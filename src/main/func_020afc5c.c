/* func_020afc5c @ 0x020afc5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_020b01f0(void *);
extern char data_021f49ec[];

int func_020afc5c(void)
{
    if (func_02073d90(data_020ccf94) != 0) {
        return func_020b01f0(data_021f49ec);
    }
    return 1;
}
