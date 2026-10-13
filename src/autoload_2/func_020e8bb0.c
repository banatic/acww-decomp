/* func_020e8bb0 @ 0x020e8bb0, 0xc0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int value;
} SmoothVal;

int func_020e8bb0(SmoothVal *self, int target, int num, int maxStep, int minStep)
{
    if (self->value != target) {
        int diff = target - self->value;
        int step = (int) (((long long) diff * num + 0x800) >> 12);
        int negMinStep;
        if (step >= minStep || step <= (negMinStep = -minStep)) {
            if (step > maxStep) {
                step = maxStep;
            }
            if (step < -maxStep) {
                step = -maxStep;
            }
            self->value = self->value + step;
        } else if (step > 0) {
            if (step < minStep) {
                self->value = self->value + minStep;
                if (self->value > target) {
                    self->value = target;
                }
            }
        } else {
            if (step > negMinStep) {
                self->value = self->value + negMinStep;
                if (self->value < target) {
                    self->value = target;
                }
            }
        }
    }
    {
        int d = target - self->value;
        return d < 0 ? -d : d;
    }
}
