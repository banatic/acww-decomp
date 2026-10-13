/* func_02082fbc @ 0x02082fbc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1a04;
extern void func_020830d0(void *obj);

void *func_02082fbc(void *obj)
{
    *(void **) obj = &data_020e1a04;
    func_020830d0(obj);
    return obj;
}
