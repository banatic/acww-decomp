/* func_020b962c @ 0x020b962c, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f6c74;
extern unsigned int data_021f6c78;
extern unsigned int data_021f6c7c;
extern unsigned int data_021f6c80;
extern unsigned int data_021f6c84;
extern unsigned int data_021f6c88;
extern unsigned int data_021f6c8c;
extern unsigned int data_021f6c90;
extern void func_020b9478(void);
extern void OS_Terminate(void);

void func_020b962c(unsigned int *out, unsigned int n)
{
    unsigned int a, b;

    a = data_021f6c74 - data_021f6c84;
    b = data_021f6c78 - data_021f6c88;
    if (a >= n) {
        if (b >= n && (b - n) * 2 > (a - n)) {
            *out = data_021f6c78 - n;
            data_021f6c78 = *out;
        } else {
            *out = data_021f6c74 - n;
            data_021f6c74 = *out;
        }
    } else if (b >= n) {
        *out = data_021f6c78 - n;
        data_021f6c78 = *out;
    } else {
        a = data_021f6c80 - data_021f6c90;
        b = data_021f6c7c - data_021f6c8c;
        if (a >= n) {
            if (b >= n && (b - n) * 2 > (a - n)) {
                *out = data_021f6c7c - n;
                data_021f6c7c = *out;
            } else {
                *out = data_021f6c80 - n;
                data_021f6c80 = *out;
            }
        } else if (b >= n) {
            *out = data_021f6c7c - n;
            data_021f6c7c = *out;
        } else {
            func_020b9478();
            OS_Terminate();
            *out = 0;
        }
    }
}
