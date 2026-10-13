/* func_ov045_0226047c @ 0x0226047c, 0x20 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a887c(void *obj);
extern void func_020edb3c(void *obj);
extern char data_ov045_0226142c[];

void *func_ov045_0226047c(void *obj)
{
    *(void **) obj = data_ov045_0226142c;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}
