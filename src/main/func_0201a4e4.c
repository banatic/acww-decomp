/* func_0201a4e4 @ 0x0201a4e4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209129c(int);
extern void func_0201a5b0(int *);

void func_0201a4e4(int *array)
{
    int i;
    int local;
    local = 0;
    for (i = 0; i < 4; i++) {
        if (array[i] == ~local) {
            continue;
        }
        func_0209129c(array[i]);
        array[i] = ~local;
    }
    func_0201a5b0(array);
}
