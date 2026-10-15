/* func_ov045_0226050c @ 0x0226050c, 0x18 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *);
extern void *data_ov045_02261414;

void *func_ov045_0226050c(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = &data_ov045_02261414;
    return obj;
}
