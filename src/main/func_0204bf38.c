/* func_0204bf38 @ 0x0204bf38, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0206213c(void);
extern void *func_0204bdd0(int i);
extern void func_0204b3cc(void *dest, void *src);
extern int func_0204be38(void *p);
extern void func_0204bf18(void *obj, void *p);
extern void func_020051b0(void *p);

void func_0204bf38(void *obj, unsigned int idx)
{
    unsigned int i, count;
    unsigned int tmp;

    if (idx >= func_0206213c()) {
        idx = 0;
    }
    count = 0;
    i = count;
    while (i < 33) {
        func_0204b3cc(&tmp, func_0204bdd0(i));
        if (func_0204be38(&tmp) != 0) {
            if (idx == count) {
                func_0204bf18(obj, &tmp);
                func_020051b0(&tmp);
                return;
            } else {
                count++;
            }
        }
        func_020051b0(&tmp);
        i++;
    }
    func_0204b3cc(obj, func_0204bdd0(0));
}
