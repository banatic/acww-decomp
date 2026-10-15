/* func_02066a84 @ 0x02066a84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *obj);
extern char data_020def4c;

void *func_02066a84(void *obj)
{
    *(void **) obj = (void *) &data_020def4c;
    func_020a8c38(obj);
    return obj;
}
