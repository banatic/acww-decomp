/* func_ov052_022604ec @ 0x022604ec, 0x68 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x800];
} SelfType;

extern void *func_02095794(int arg);
extern int func_02030818(void *ptr);
extern void func_ov052_022610cc(void *ptr, int arg);
extern void func_0203e0a8(void *self, int arg);
extern void func_ov052_02261908(void *self, int arg);

int func_ov052_022604ec(SelfType *self)
{
    void *result;
    unsigned int local[3];

    result = func_02095794(4);
    local[0] = ((unsigned int *) result)[0];
    local[1] = ((unsigned int *) result)[1];
    local[2] = ((unsigned int *) result)[2];

    if (func_02030818(local) != 0) {
        if (self->data[0x732] == 0) {
            func_ov052_022610cc((char *) self + 0x658, 1);
        } else {
            func_ov052_022610cc((char *) self + 0x658, 2);
        }

        func_0203e0a8(self, 0);
        func_ov052_02261908(self, 0xa);

        return 1;
    }

    return 0;
}
