/* func_ov050_02260528 @ 0x02260528, 0x98 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void);
extern int func_02073d90(void *);
extern short *func_0209d358(int, int);
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern int func_0208602c(void);
extern int func_020860d0(int argument0);
extern int func_02087ec0(void *argument0);
extern int func_ov050_02260510(void *);
extern int func_ov050_022604e0(void *);
extern void func_ov050_02263640(void *, int);
extern int func_0203e0a8(void *, int);
extern void *data_020ccf94;

int func_ov050_02260528(void *obj)
{
    if (func_0203ec98() != 0) {
        return 0;
    }
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        return 0;
    }
    if (func_02099020(func_020984e8(), 1) != 0) {
        return 0;
    }

    if (func_02087ec0((void *) func_020860d0(func_0208602c())) != 0) {
        if (func_ov050_02260510(obj) != 0) {
            func_ov050_02263640((char *) obj + 0x658, 6);
        } else if (func_ov050_022604e0(obj) != 0) {
            func_ov050_02263640((char *) obj + 0x658, 0x1d);
        }
        func_0203e0a8(obj, 0);
        return 1;
    }
    return 0;
}
