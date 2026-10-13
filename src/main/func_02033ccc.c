/* func_02033ccc @ 0x02033ccc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202ff00(void *);
extern void func_020342a4(void *);
extern char data_020da21c;

void *func_02033ccc(void *obj)
{
    func_0202ff00(obj);
    func_020342a4((char *) obj + 0x38);
    *(void **) obj = &data_020da21c;
    return obj;
}
