/* func_ov077_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov077_02278d4c(void *);
extern void *func_0202ee5c(void *);

extern unsigned char data_ov077_0227988c[];

void *func_ov077_02278a00(void *obj)
{
    *(void **) obj = (void *) data_ov077_0227988c;
    func_ov077_02278d4c((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
