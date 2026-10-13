/* func_ov002_02207e08 @ 0x02207e08, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov002_0220baa8;
extern void func_0208ad24(void *);
extern void func_020edb3c(void *);

void *func_ov002_02207e08(void *obj)
{
    *(void **) obj = &data_ov002_0220baa8;
    func_0208ad24(obj);
    func_020edb3c(obj);
    return obj;
}
