/* func_ov108_0229d588 @ 0x0229d588, 0x98 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov002_02208e28(void *p);
extern int func_ov002_02208054(void *p, int a);
extern void func_ov108_0229c468(void *p);
extern int func_ov002_02208b00(void *p, int a, int b);
extern void func_ov002_02209114(void *p, int a, int b);
extern void func_ov002_02208098(void *p, int a);

void func_ov108_0229d588(unsigned char *obj)
{
    int result;
    int flag;
    unsigned char *p;

    if (func_ov002_02208e28(obj + 0x24fc) == 0) {
        return;
    }
    if (func_ov002_02208054(obj, 1) != 0) {
        func_ov108_0229c468(obj);
        return;
    }

    if (data_021fbdd8 && data_021fbddc) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        result = func_ov002_02208b00(obj + 0x24fc, data_021f6c58, data_021f6c54);
        if (result < 0) {
            return;
        }
        func_ov002_02209114(obj + 0x24fc, result, 1);
        p = obj + result;
        obj[0x2b4] = p[0x28e9];
        func_ov002_02208098(obj, 0x14);
    }
}
