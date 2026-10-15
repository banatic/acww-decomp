/* func_02040980 @ 0x02040980, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7a8[];
extern int func_0209ded0(void);
extern void func_0209e474(void *ptr);
extern void *func_020409c8(void *ptr, int count);

void *func_02040980(void *context)
{
    char *base = (char *) data_021dc7a8;
    void *result = 0;
    int status = func_0209ded0();

    if (status != 0) {
        struct {
            int a;
            int b;
        } local;
        local.a = 0;
        local.b = 0;

        func_0209e474(&local);
        if (((unsigned char *) &local)[2] < 6) {
            status--;
        }
        result = func_020409c8(base + 0x17218, status);
    }

    return result;
}
