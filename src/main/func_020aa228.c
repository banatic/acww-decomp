/* func_020aa228 @ 0x020aa228, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __thumb func_020aaea4(void *);
extern void __thumb func_020ac078(void *);
extern void __thumb func_020aa7fc(void *);
extern void __arm func_020edb3c(void *);
extern unsigned char data_020e404c[];

void *func_020aa228(void *obj)
{
    *(void **) obj = data_020e404c;
    func_020aaea4((char *) obj + 0x154);
    func_020ac078((char *) obj + 0xc);
    func_020aa7fc(obj);
    func_020edb3c(obj);
    return obj;
}
