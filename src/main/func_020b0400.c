/* func_020b0400 @ 0x020b0400, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_020996ac(void *);
extern int func_0203cdcc(int, void *);
extern int func_020644cc(int);
extern void func_020b048c(int);
extern unsigned short data_020d1e74[];

void func_020b0400(void)
{
    unsigned short local[2];
    int count;
    unsigned int i;
    int target;
    void *obj;

    obj = func_020984e8();
    if (obj == 0) {
        return;
    }

    count = 0;
    i = count;
    do {
        local[0] = data_020d1e74[i];
        if (func_0203cdcc(func_020996ac(obj), &local[0]) == 0) {
            count++;
        }
        i++;
    } while (i < 13);

    if (count != 0) {
        target = func_020644cc(count);
        count = 0;
        i = count;
        while (i < 13) {
            local[1] = data_020d1e74[i];
            if (func_0203cdcc(func_020996ac(obj), &local[1]) == 0) {
                if (count == target) {
                    func_020b048c(i);
                    return;
                }
                count++;
            }
            i++;
        }
    }

    func_020b048c(func_020644cc(13));
}
