/* approach_3: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e8bb0 @ 0x020e8bb0, 0xc0 bytes, ARM
 * func_020e8b60 @ 0x020e8b60, 0x50 bytes, ARM
 * func_020e8b4c @ 0x020e8b4c, 0x14 bytes, ARM
 * func_020e8b0c @ 0x020e8b0c, 0x40 bytes, ARM
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

void func_020e8b60(int *p, int target, int scale, int max)
{
    int delta;
    int inc;

    if (*p == target) {
        return;
    }

    delta = target - *p;
    inc = (int) (((long long) delta * scale + 0x800) >> 12);

    if (inc > max) {
        inc = max;
    } else if (inc < -max) {
        inc = -max;
    }

    *p += inc;
}

int func_020e8b4c(int a, int b)
{
    int diff = a - b;
    diff = (short) diff;
    if (diff < 0) {
        diff = -diff;
    }
    return diff;
}

int func_020e8b0c(int a, int b, int c)
{
    if (b < c) {
        int result = 0;
        if (a >= b) {
            result = (a <= c);
        }
        return result;
    } else {
        int result = 0;
        if (a >= c) {
            result = (a <= b);
        }
        return result;
    }
}
