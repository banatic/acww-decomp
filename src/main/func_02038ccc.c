/* func_02038ccc @ 0x02038ccc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *obj);
extern void func_020a8c1c(void *obj);

extern unsigned char data_020da560[];

void *func_02038ccc(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = (void *) data_020da560;
    func_020a8c1c(obj);
    return obj;
}
