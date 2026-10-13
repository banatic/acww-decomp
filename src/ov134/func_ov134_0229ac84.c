/* func_ov134_0229ac84 @ 0x0229ac84, 0x48 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

int func_ov134_0229ac84(int unused, int *cur, int target, int max_step, int min_step)
{
    int diff;
    int step;
    int value;

    value = *cur;
    diff = value > target ? value - target : target - value;
    if (diff < min_step) {
        *cur = target;
        return 1;
    }
    step = diff >> 1;
    if (step > max_step) {
        step = max_step;
    } else if (step < min_step) {
        step = min_step;
    }
    if (value > target) {
        *cur -= step;
    } else {
        *cur += step;
    }
    return 0;
}
