/* func_02082ed4 @ 0x02082ed4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *);
extern char data_020e1a54[];

void *func_02082ed4(void *obj)
{
    *(char **) obj = data_020e1a54;
    func_020830d0(obj);
    return obj;
}
