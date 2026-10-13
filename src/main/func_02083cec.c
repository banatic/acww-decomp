/* func_02083cec @ 0x02083cec, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02084f84(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e1cc0[];

void *func_02083cec(void *obj)
{
    *(void **) obj = (void *) data_020e1cc0;
    func_02084f84((char *) obj + 0x50);
    *(void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
