/* func_ov096_0229e71c @ 0x0229e71c, 0x80 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e6b0(void *);
extern void func_ov096_0229fb9c(void *);
extern void func_ov096_0229f874(void *, int, int, int);
extern void func_ov096_0229e82c(void *, int);
extern int func_ov096_0229da6c(void *, int);
extern void func_ov096_0229e6a0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229c2dc(void *, int);

int func_ov096_0229e71c(void *param)
{
    if (func_ov096_0229e6b0(param) == 0) {
        func_ov096_0229fb9c(param);
        func_ov096_0229f874(param, 9, 0xff, 1);
        func_ov096_0229e82c(param, 1);
        return 0;
    } else {
        typedef struct {
            char pad[0xac];
            unsigned short field;
        } UnkStruct_0229e71c;
        unsigned short s = ((UnkStruct_0229e71c *) param)->field;
        int ret = func_ov096_0229da6c(param, s);
        if (ret == 0) {
            func_ov096_0229e82c(param, 1);
            return 0;
        } else if (ret == 1) {
            func_ov096_0229e6a0(param);
            return 1;
        } else if (ret == 2) {
            func_ov002_02208098((void *) (param), 0x28);
            func_ov096_0229c2dc(param, 0x1000);
            return 0;
        } else {
            func_ov096_0229e82c(param, 1);
            return 0;
        }
    }
}
