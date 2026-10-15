/* func_ov003_0221b6d4 @ 0x0221b6d4, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203f130(void *);
extern void *func_02066a30(void *);
extern void *func_0205577c(void *);
extern void *func_02032c64(void *);
extern void *func_ov003_0221b77c(void *);
extern void func_020f5958(void *);
extern char data_ov003_022382ac;
extern char data_ov003_02238314;

void *func_ov003_0221b6d4(void *obj)
{
    func_0203f130(obj);
    func_02066a30((char *) obj + 0xec);
    *(void **) obj = &data_ov003_022382ac;
    *(void **) ((char *) obj + 0xec) = &data_ov003_02238314;
    func_0205577c((char *) obj + 0x134);
    func_0205577c((char *) obj + 0x1d0);
    func_02032c64((char *) obj + 0x274);
    func_ov003_0221b77c((char *) obj + 0x2a4);
    func_020f5958((char *) obj + 0x328);
    *(unsigned short *) ((char *) obj + 0x39a) = 0xFFF1;
    return obj;
}
