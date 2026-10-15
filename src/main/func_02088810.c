/* func_02088810 @ 0x02088810, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b5630(void *);
extern void *func_020984e8(void);
extern void *func_02094fd4(void *);
extern void *func_02099670(void *);
extern int func_02099020(void *, int);
extern void func_02098fd0(void *, int);
extern int func_020644cc(int);
extern int func_0208893c(void *, int, unsigned short *);
extern unsigned int func_02088a74(void *);
extern int func_020b45d0(void *, unsigned int, int, int, int, int);
extern int func_0203d7c4(int, void *);
extern void *func_02094fbc(void *);
extern void *func_020b5618(void *);
void func_02088810(void *boss)
{
    unsigned short arr[3];
    unsigned int buf1[0x10];
    unsigned char buf2[0x24];
    int param;
    void *obj;
    void *vo;
    int p;
    unsigned int count;
    func_020b5630(buf1);
    obj = func_020984e8();
    func_02094fd4(buf2);
    vo = func_02099670(obj);
    if (func_02099020(obj, 0x17)) {
        if (func_02099020(obj, 0x19)) {
            arr[0] = 0x1492;
            p = func_020644cc(2);
            if (func_0208893c(boss, p, arr)) {
                func_02098fd0(obj, 0x19);
            }
        }
        if (func_02099020(obj, 0x1a)) {
            arr[1] = 0x1492;
            p = func_020644cc(2);
            p += 2;
            if (func_0208893c(boss, p, &arr[1])) {
                func_02098fd0(obj, 0x1a);
            }
        }
    }
    if (func_02099020(obj, 0x18)) {
        if (func_02088a74(vo) >= 1) {
            func_020b45d0(buf1, func_02088a74(vo), 10, 0, 0, 0);
            func_0203d7c4(3, buf1);
            p = func_020644cc(2);
            param = p + 4;
            count = func_02088a74(vo);
            if (count >= 10) {
                count = 10;
                param = 6;
            }
            func_020b45d0(buf1, count * 100, 10, 0, 0, 0);
            func_0203d7c4(4, buf1);
            arr[2] = count + 0x1491;
            if (func_0208893c(boss, param, &arr[2])) {
                ((unsigned char *) boss)[0xf] = 0;
            }
        }
    }
    func_02094fbc(buf2);
    func_020b5618(buf1);
}
