/* func_ov003_02225538 @ 0x02225538, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int w[12];
} Big;
void func_ov003_022251a4(void *self, void *o, Big s);
int func_02049ec4(void *a);

void *func_ov003_02225538(char *self, void *a, Big s)
{
    void *o = self + 0x1590 + 0x618 * func_02049ec4(a);
    func_ov003_022251a4(self, o, s);
    return o;
}
