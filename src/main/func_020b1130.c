/* func_020b1130 @ 0x020b1130, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021ee418;
extern void *func_020900e4(int *ptr);
extern void func_020b1a24(void *);
extern void *func_020b15b0(void);
extern int func_020b1974(void *list, int i);
extern int func_020644cc(int n);
extern int func_020b1530(int i);
extern void *func_020b1a0c(void *obj, int x);

void func_020b1130(void)
{
    void *obj;
    void *list;
    int count;
    int i;

    obj = func_020900e4(&data_021ee418);
    func_020b1a24(obj);
    count = 0;
    list = func_020b15b0();

    i = 0;
    do {
        if (func_020b1974(list, i) != 0) {
            count++;
        }
        i++;
    } while (i < 16);

    if (count == 0) {
        return;
    }

    count = func_020644cc(count);

    i = 0;
    while (i < 16) {
        if (func_020b1974(list, i) != 0) {
            if (count > 0) {
                count--;
            } else {
                func_020b1a0c(obj, func_020b1530(i));
                return;
            }
        }
        i++;
    }
}
