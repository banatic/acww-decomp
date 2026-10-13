/* func_02066670 @ 0x02066670, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *, void *);

extern unsigned char data_020de760[];

void *func_02066670(void *obj)
{
    void *ptr = (void *) data_020de760;
    *(void **) obj = ptr;
    func_020edb3c(obj, ptr);
    return obj;
}
