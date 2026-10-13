/* func_ov114_0229c690 @ 0x0229c690, 0x68 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229c60c(void *arg);
extern int func_ov090_022990b8(int value);
extern int func_ov002_0220a4f8(void *ptr);
extern int data_ov114_0229da94[];

int func_ov114_0229c690(void *arg)
{
    if (func_ov114_0229c60c(arg) != -1) {
        return func_ov090_022990b8(((unsigned char *) arg)[0x12bc] - 5);
    } else {
        unsigned char b = ((unsigned char *) arg)[0x12bc];
        if (b == 4) {
            return func_ov002_0220a4f8((char *) arg + 0x121c);
        } else if (b < 4) {
            return data_ov114_0229da94[b];
        } else {
            return 27 * (b - 13) + 34 - *(int *) ((char *) arg + 0x127c) - *(int *) ((char *) arg + 0x1280);
        }
    }
}
