/* func_ov118_0229bccc @ 0x0229bccc, 0x48 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8; // 0x021fbdd8
extern unsigned char data_021f6c54; // 0x021f6c54
extern void *func_0208e95c(unsigned char *p, int n);
extern void func_ov118_0229b8b0(unsigned char *p);
extern void func_ov118_0229ac44(unsigned char *p, int n);

void func_ov118_0229bccc(unsigned char *obj)
{
    if (data_021fbdd8 == 0) {
        func_0208e95c(obj + 0x678, 3);
        func_ov118_0229b8b0(obj);
    }
    func_ov118_0229ac44(obj, obj[0xa7] + (data_021f6c54 - obj[0xa5]));
}
