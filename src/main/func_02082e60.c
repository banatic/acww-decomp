/* func_02082e60 @ 0x02082e60, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *obj);
extern char data_020e1a7c[];

void *func_02082e60(void *obj)
{
    *(void **) obj = data_020e1a7c;
    func_020830d0(obj);
    return obj;
}
