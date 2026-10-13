/* func_ov068_022667e0 @ 0x022667e0, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov068_022771c0;
extern void func_ov068_02266f3c(void *);
extern void func_02012588(void *);
extern void func_ov068_0226ce48(void *);
extern void func_ov068_02266cec(void *);
extern void func_0202e5e0(void *);

void *func_ov068_022667e0(void *param)
{
    *(unsigned int *) param = (unsigned int) &data_ov068_022771c0;
    func_ov068_02266f3c((char *) param + 0x9f4);
    func_02012588((char *) param + 0x9b4);
    func_ov068_0226ce48((char *) param + 0x8b8);
    func_ov068_02266cec((char *) param + 0x898);
    func_0202e5e0(param);
    return param;
}
