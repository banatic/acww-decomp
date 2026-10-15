/* func_ov109_0229c9f0 @ 0x0229c9f0, 0x40 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(void *object, unsigned int index);
extern unsigned char func_ov109_0229cc98(void *object, int index);
extern void func_ov094_0229ab1c(void *object, int index);
extern void func_ov094_0229b98c(void *object);
extern void func_ov109_0229ca30(void *object);

void func_ov109_0229c9f0(void *object, unsigned int index)
{
    if (func_ov109_0229ccb4(object, index)) {
        func_ov094_0229ab1c((char *) object + 0xcc, func_ov109_0229cc98(object, index));
        func_ov094_0229b98c((char *) object + 0xb2c);
    } else {
        func_ov109_0229ca30(object);
    }
}
