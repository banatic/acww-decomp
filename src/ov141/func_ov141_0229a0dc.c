/* func_ov141_0229a0dc @ 0x0229a0dc, 0x98 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_02299888(unsigned char *, int, unsigned char, int, int);
extern void func_ov139_02299798(unsigned char *, int);
extern int func_ov141_02299f94(unsigned char *, int);

void func_ov141_0229a0dc(unsigned char *self)
{
    int i;
    int a = -1;

    i = 0;
    do {
        switch (*(self + i + 0x1a7f)) {
            case 1:
                if (*(self + i + 0x1a85) < 5) {
                    *(self + i + 0x1a85) += 1;
                    func_ov139_02299888(self + 0x94, i, *(self + i + 0x1a85), 5, 14);
                }
                break;
            case 2:
                if (*(self + i + 0x1a85) > 1) {
                    *(self + i + 0x1a85) -= 1;
                    func_ov139_02299888(self + 0x94, i, *(self + i + 0x1a85), 5, 14);
                } else {
                    *(self + i + 0x1a7f) = 0;
                    func_ov139_02299798(self + 0x94, i);
                    if (*(int *) (self + 0x1270) == i) {
                        func_ov141_02299f94(self, a);
                    }
                }
                break;
        }
        i++;
    } while (i < 6);
}
