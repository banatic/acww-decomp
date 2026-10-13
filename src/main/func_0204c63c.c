/* func_0204c63c @ 0x0204c63c, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02061e2c(void *, void *);
extern int func_0204bcf8(void *);
extern int func_0204b42c(void *);
extern void NNS_FndAllocFromAllocator(void *, int);
extern int func_02062780(void *);
extern void func_020051b0(void *);
extern int func_0204c5ec(void *);

int func_0204c63c(void *param)
{
    unsigned char local[8];
    int v;

    func_02061e2c(local, param);
    v = func_0204bcf8(local);
    switch (v) {
        case 1: {
            int r;
            int result;

            r = func_0204b42c(local);
            NNS_FndAllocFromAllocator(local + 2, r);
            result = func_02062780(local + 2);
            func_020051b0(local + 2);
            func_020051b0(local);
            return result;
        }
        case 3:
        case 4:
            if (func_0204c5ec(local) != 0) {
                func_020051b0(local);
                return 1;
            } else {
                func_020051b0(local);
                return 0;
            }
        default:
            func_020051b0(local);
            return 0;
    }
}
