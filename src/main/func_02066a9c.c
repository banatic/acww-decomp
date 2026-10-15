/* func_02066a9c @ 0x02066a9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *obj);
extern void func_020a8c1c(void *obj);
extern unsigned int data_020def4c;

void *func_02066a9c(void *obj)
{
    func_020a8cac(obj);
    *(unsigned int *) obj = (unsigned int) &data_020def4c;
    func_020a8c1c(obj);
    return obj;
}
