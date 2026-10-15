/* func_02084210 @ 0x02084210, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} Object;

extern Object *data_020ccf94;
extern unsigned char data_020e54a8;
extern int func_02073dd4(Object *, unsigned int);
extern int func_02084af0(void);
extern int func_020883cc(void);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern void func_02087f58(void *);

void func_02084210(void *receiver)
{
    unsigned int flag;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        return;
    }
    if (func_02084af0() != 0) {
        return;
    }
    if (func_020883cc() == 0) {
        return;
    }

    flag = (data_020e54a8 != 0) ? 0 : 1;
    if (flag > 0) {
        func_02087f58((void *) func_020860c4((int) func_0208602c()));
    }
}
