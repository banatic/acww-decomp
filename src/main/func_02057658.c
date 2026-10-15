/* func_02057658 @ 0x02057658, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057640(void *);
extern void func_02057764(void *);
extern void *func_020578d4(void *);
extern void func_02057054(void *);
extern void func_020edb3c(void *);
extern unsigned char data_020dd194;

void *func_02057658(void *obj)
{
    ((unsigned int *) obj)[0] = (unsigned int) &data_020dd194;
    func_02057640(obj);
    func_02057764((char *) obj + 0x65);
    func_02057764((char *) obj + 0x54);
    func_020578d4((char *) obj + 0x18);
    func_02057054(obj);
    func_020edb3c(obj);
    return obj;
}
