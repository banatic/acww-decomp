/* func_02082d78 @ 0x02082d78, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *obj);
extern unsigned int data_020e19dc[];

void *func_02082d78(void *obj)
{
    *(void **) obj = data_020e19dc;
    func_020830d0(obj);
    return obj;
}
