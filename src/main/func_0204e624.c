/* func_0204e624 @ 0x0204e624, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80c0;
extern void func_0204e420(void *p);
extern void func_0204e510(void *p, void *param);
extern void func_020e993c(void *param, void *p);
extern void func_0205c13c(void);

void func_0204e624(void *param)
{
    if (data_021c80c0) {
        func_0204e420(data_021c80c0);
        func_0204e510(data_021c80c0, param);
        func_020e993c(param, data_021c80c0);
        data_021c80c0 = 0;
    }
    func_0205c13c();
}
