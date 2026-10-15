/* func_ov046_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov046_022612ec(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);

extern unsigned char data_ov046_022620e0[];

void *func_ov046_02260448(void *obj)
{
    *(void **) obj = (void *) data_ov046_022620e0;
    func_ov046_022612ec((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
