/* func_0203de10 @ 0x0203de10, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a40(void *, void *);
extern void func_020edb3c(void *);

extern unsigned char data_020da994[];

void *func_0203de10(void *obj)
{
    *(void **) obj = (void *) data_020da994;
    func_020a9a40(obj, (void *) data_020da994);
    func_020edb3c(obj);
    return obj;
}
