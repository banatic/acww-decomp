/* func_ov073_02279020 @ 0x02279020, 0x30 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_0208b514(unsigned int context);
extern void func_ov073_02279608(void *obj, int arg);

int func_ov073_02279020(void *obj)
{
    if (!func_02014868((char *) obj + 0x618)) {
        func_0208b514(func_0203e020(obj));
        func_ov073_02279608(obj, 1);
    }
    return 1;
}
