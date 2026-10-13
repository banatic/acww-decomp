/* func_02089ca4 @ 0x02089ca4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a088(void *obj);

extern unsigned char data_020e2008[];

void *func_02089ca4(void *obj)
{
    func_0208a088(obj);
    *(void **) obj = (void *) data_020e2008;
    *(int *) ((char *) obj + 0x40) = 0;
    return obj;
}
