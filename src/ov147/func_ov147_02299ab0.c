/* func_ov147_02299ab0 @ 0x02299ab0, 0x20 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066994(void *, void *);
extern void func_020edb3c(void *);
extern char data_ov147_0229aae4;

void *func_ov147_02299ab0(void *obj)
{
    void *p;
    p = &data_ov147_0229aae4;
    *((void **) obj) = p;
    func_02066994(obj, p);
    func_020edb3c(obj);
    return obj;
}
