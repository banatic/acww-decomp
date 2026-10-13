/* func_020aa740 @ 0x020aa740, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e406c;
extern void func_020ab36c(void *);
extern void func_020ac2c8(void *);
extern void func_020aa7fc(void *);
extern void func_020edb3c(void *);

void *func_020aa740(void *obj)
{
    *(void **) obj = &data_020e406c;
    func_020ab36c((void *) ((char *) obj + 0x84));
    func_020ac2c8((void *) ((char *) obj + 0xc));
    func_020aa7fc(obj);
    func_020edb3c(obj);
    return obj;
}
