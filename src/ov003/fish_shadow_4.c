/* fish_shadow_4: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222c434 @ 0x0222c434, 0x20 bytes, Thumb
 * func_ov003_0222c41c @ 0x0222c41c, 0x18 bytes, Thumb
 * func_ov003_0222c418 @ 0x0222c418, 0x2 bytes, Thumb
 * func_ov003_0222c414 @ 0x0222c414, 0x2 bytes, Thumb
 */

extern int data_ov003_0223c0d4;
void *func_02056578(void *self);
void func_020edb3c(void *self);
void *func_020edf70(unsigned int n);
void *func_ov003_02228e8c(void *p);

void *func_ov003_0222c434(void *self)
{
    *(int *) self = (int) &data_ov003_0223c0d4;
    func_02056578(self);
    func_020edb3c(self);
    return self;
}

void *func_ov003_0222c41c(void)
{
    void *p = func_020edf70(0x88);
    if (p != 0) {
        p = func_ov003_02228e8c(p);
    }
    return p;
}

void func_ov003_0222c418(void *self, int v) {}

void func_ov003_0222c414(void *object)
{
    (void) object;
}
