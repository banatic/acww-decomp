/* func_02082e04 @ 0x02082e04, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *obj);
extern char data_020e1a68;

void *func_02082e04(void *obj)
{
    func_02083100(obj);
    *(void **) obj = &data_020e1a68;
    return obj;
}
