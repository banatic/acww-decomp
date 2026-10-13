/* func_020b5cd4 @ 0x020b5cd4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5460[];

void *func_020b5cd4(void *obj)
{
    *(void **) obj = (void *) data_020e5460;
    *(void **) obj = (void *) data_020e3c94;
    *(void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
