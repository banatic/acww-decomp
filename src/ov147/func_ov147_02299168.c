/* func_ov147_02299168 @ 0x02299168, 0xe0 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;
extern void func_ov147_02299248(void *receiver);
extern void func_ov147_022990dc(void *self);
extern void func_ov147_0229a630(int *p0, int p1);
extern int func_ov147_02299018(void *self);
extern void func_ov147_02299008(void *self);
extern int func_ov147_02298f88(void *self);

void func_ov147_02299168(unsigned char *self)
{
    switch (*(unsigned char *) (self + 0xaa)) {
        case 0: {
            unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
            if (flag == 0) {
                break;
            }
            func_ov147_02299248(self);
            func_ov147_022990dc(self);
            break;
        }
        case 6: {
            unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
            if (flag == 0) {
                break;
            }
            func_ov147_0229a630((int *) (self + 0xb0), 1);
            *(unsigned short *) (self + 0xac) = 0xe10;
            *(unsigned char *) (self + 0xaa) = 5;
            break;
        }
        case 1: {
            if (func_ov147_02299018(self) == 0) {
                break;
            }
            *(unsigned char *) (self + 0xaa) = 2;
            if (*(unsigned char *) (self + 0xab) == 0) {
                func_ov147_0229a630((int *) (self + 0xb0), 0);
            }
            break;
        }
        case 2: {
            if (*(unsigned short *) (self + 0xa8) != 0) {
                (*(unsigned short *) (self + 0xa8))--;
            } else {
                func_ov147_02299008(self);
                func_ov147_0229a630((int *) (self + 0xb0), 1);
            }
            break;
        }
        case 3: {
            if (func_ov147_02298f88(self) != 0) {
                *(unsigned char *) (self + 0xaa) = 4;
            }
            break;
        }
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
}
