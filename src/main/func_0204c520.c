/* func_0204c520 @ 0x0204c520, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02061e2c(void *dst, int src);
extern int func_0204bcf8(void *p);
extern unsigned int func_0204b42c(int arg);
extern void NNS_FndAllocFromAllocator(void *object, unsigned int value);
extern void *func_02062870(void *p);
extern void func_020051b0(void *p);
extern int func_0204bcdc(void *p);
extern int func_0204c614(void *p);
extern int func_0204c5ec(void *p);
extern int func_0204c5c4(void *p);

int func_0204c520(int arg)
{
    struct {
        unsigned short head;
        unsigned char body[6];
    } local;
    void *result;

    func_02061e2c(&local, arg);
    if (func_0204bcf8(&local) == 1) {
        NNS_FndAllocFromAllocator(&local.body[0], func_0204b42c(arg));
        result = func_02062870(&local.body[0]);
        func_020051b0(&local.body[0]);
        func_020051b0(&local);
        return (int) result;
    } else {
        if (func_0204bcdc(&local) != 0) {
            if (func_0204c614(&local) != 0) {
                func_020051b0(&local);
                return 0x39;
            }
            if (func_0204c5ec(&local) != 0) {
                func_020051b0(&local);
                return 0x3a;
            }
            if (func_0204c5c4(&local) != 0) {
                func_020051b0(&local);
                return 0x3a;
            }
            func_020051b0(&local);
            return 0x3b;
        } else {
            func_020051b0(&local);
            return 0;
        }
    }
}
