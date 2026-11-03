/* fox_tent_talk_2: 6 functions, module ov052
 * mwccarm 1.2/base -O4,s
 * func_ov052_0226118c @ 0x0226118c, 0x1e bytes, Thumb
 * func_ov052_02261158 @ 0x02261158, 0x34 bytes, Thumb
 * func_ov052_02261140 @ 0x02261140, 0x18 bytes, Thumb
 * func_ov052_02261128 @ 0x02261128, 0x18 bytes, Thumb
 * func_ov052_02261108 @ 0x02261108, 0x20 bytes, Thumb
 * func_ov052_02261100 @ 0x02261100, 0x8 bytes, Thumb
 */

extern int func_020644cc(int value);
extern void *func_0202eb70(void *obj);
extern char data_ov052_02261eb0[];
extern void *func_0202eb20(void *a);
extern void func_020edb3c(void *p);
extern void func_0201612c(void *parameter0);

int func_ov052_0226118c(int unused, const unsigned char *s, int n)
{
    int count = 0;
    int i = count;
    while (i < n) {
        if (*s == 0) {
            count++;
        }
        s++;
        i++;
    }
    return count;
}

int func_ov052_02261158(int a, const unsigned char *arr, int n)
{
    const unsigned char *p;
    int tmp;
    int result;
    int pos;
    int i;

    p = arr;
    tmp = func_ov052_0226118c(a, arr, n);
    result = 0;
    pos = func_020644cc(tmp);
    i = 0;

    while (i < n) {
        if (*p == 0) {
            if (pos == 0) {
                result = i;
                break;
            }
            pos--;
        }
        p++;
        i++;
    }

    return result;
}

void *func_ov052_02261140(void *obj)
{
    func_0202eb70(obj);
    *(void **) obj = (void *) data_ov052_02261eb0;
    return obj;
}

void *func_ov052_02261128(void *p)
{
    *(void **) p = ((char *) data_ov052_02261eb0);
    func_0202eb20(p);
    return p;
}

void *func_ov052_02261108(void *p)
{
    *(void **) p = ((char *) data_ov052_02261eb0);
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}

void func_ov052_02261100(void *arg0)
{
    func_0201612c((void *) arg0);
}
