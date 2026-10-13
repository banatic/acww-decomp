/* func_02062c0c @ 0x02062c0c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cb5b0;
extern int data_021cb5c0;
extern int func_0206266c(void *p);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);

void func_02062c0c(void)
{
    unsigned short i;
    struct {
        unsigned short a;
        unsigned short b;
    } local;
    int flag;

    for (i = 0x1000; i < 0x156e; i++) {
        local.a = i;
        if (func_0206266c(&local) == 0) {
            continue;
        }

        if (func_0204bcdc(&data_021cb5b0) != 0) {
            local.b = 0xfff1;
            if (func_0204bc64(&data_021cb5b0) == func_0204bc64(&local.b)) {
                flag = 1;
            } else {
                flag = 0;
            }
        } else {
            if (data_021cb5b0 == 0xfff1) {
                flag = 1;
            } else {
                flag = 0;
            }
        }

        if (flag != 0) {
            data_021cb5b0 = local.a;
        }
        data_021cb5c0++;
    }
}
