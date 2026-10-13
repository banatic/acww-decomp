/* func_02097e38 @ 0x02097e38, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097eb0(void *param, int idx);
extern void func_02097e94(void *param);
extern int func_020644cc(int size);

int func_02097e38(void *param)
{
    int i;
    int count;
    int rem;

    count = 0;
    for (i = 0; i < 0x28; i++) {
        if (func_02097eb0(param, i) == 0) {
            count++;
        }
    }

    if (count == 0) {
        func_02097e94(param);
        count = 0x28;
    }

    rem = func_020644cc(count);

    for (i = 0; i < 0x28; i++) {
        if (func_02097eb0(param, i) == 0) {
            if (rem > 0) {
                rem--;
            } else {
                return i;
            }
        }
    }

    return 0;
}
