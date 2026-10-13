/* func_ov070_022796ec @ 0x022796ec, 0x38 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *obj);
extern void func_02138d6c(void *ptr, int a, int b, void (*c)(void), void (*d)(void));
extern char data_ov070_02279dbc;
extern void func_02034ce0(void);
extern void func_020051b0(void);

void *func_ov070_022796ec(void *obj)
{
    func_0202eb70(obj);
    *(void **) obj = (void *) &data_ov070_02279dbc;
    func_02138d6c((char *) obj + 0xC4, 3, 2, func_02034ce0, func_020051b0);
    return obj;
}
