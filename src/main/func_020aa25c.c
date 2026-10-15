/* func_020aa25c @ 0x020aa25c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aaea4(void *ptr);
extern void *func_020ac078(void *ptr);
extern void func_020aa7fc(void *ptr);
extern int data_020e404c;

void *func_020aa25c(void *p)
{
    *(void **) p = (void *) &data_020e404c;
    func_020aaea4((char *) p + 0x154);
    func_020ac078((char *) p + 0xc);
    func_020aa7fc(p);
    return p;
}
