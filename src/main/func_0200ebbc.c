/* func_0200ebbc @ 0x0200ebbc, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0206837c(unsigned int param);
extern unsigned int func_020ab504(void *arg0);
extern void func_0206844c(void *self, void *g, int i);
extern unsigned char data_021f43e8;

void func_0200ebbc(char *a)
{
    int state = *(int *) (a + 0x81c);

    if (state < 0xf) {
        switch (state) {
            case 0:
            case 2:
            case 3:
            case 4: {
                unsigned int ok = func_020ab504((void *) func_0206837c(*(unsigned int *) (a + 0x12c)));
                unsigned char local = data_021f43e8;

                func_0206844c((void *) (*(int *) (a + 0x12c)), &local, 0);

                if (ok == 0) {
                    *(int *) (a + 0x81c) = 5;
                } else {
                    switch (*(int *) (a + 0x81c)) {
                        case 0:
                        case 4:
                            *(int *) (a + 0x81c) = 9;
                            break;
                        case 2:
                            *(int *) (a + 0x81c) = 0xb;
                            break;
                        default:
                            *(int *) (a + 0x81c) = 0xf;
                            break;
                    }
                }
                break;
            }
            case 1:
            default:
                break;
        }
    }
}
