/* countdown_2: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221cdcc @ 0x0221cdcc, 0x74 bytes, Thumb
 * func_ov003_0221cd7c @ 0x0221cd7c, 0x50 bytes, Thumb
 * func_ov003_0221cd5c @ 0x0221cd5c, 0x20 bytes, Thumb
 * func_ov003_0221cd54 @ 0x0221cd54, 0x8 bytes, Thumb
 * func_ov003_0221cd4c @ 0x0221cd4c, 0x8 bytes, Thumb
 * func_ov003_0221cd44 @ 0x0221cd44, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x02d8];
    unsigned int arr[6];
} UnkStruct_0221cd5c;

extern void func_0209e474(int *p);
extern int _u32_div_f(int a, int b);
extern int data_ov003_0223c8bc;
extern int data_ov003_0223c8b8;
extern int data_ov003_0223c8c0;
extern void func_ov009_022632c8(void *ptr);
extern void func_020033e4(void *p, int arg);
extern int *func_ov009_02264c10(void *argument0);
extern char *func_ov009_02264be0(void *argument0);
extern void *func_ov009_02264b64(void *argument0);

int func_ov003_0221cdcc(void)
{
    int local[3];
    unsigned char sec, min, hour;
    int total, hours, minutes;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    sec = ((unsigned char *) local)[0];
    min = ((unsigned char *) local)[1];
    hour = ((unsigned char *) local)[2];
    total = (min * 60 + hour * 3600) + sec;
    data_ov003_0223c8bc = 86400 - total;
    hours = _u32_div_f(data_ov003_0223c8bc, 3600);
    data_ov003_0223c8b8 = hours;
    data_ov003_0223c8bc = data_ov003_0223c8bc - hours * 3600;
    minutes = _u32_div_f(data_ov003_0223c8bc, 60);
    data_ov003_0223c8c0 = minutes;
    data_ov003_0223c8bc = data_ov003_0223c8bc - minutes * 60;
    return 1;
}

void func_ov003_0221cd7c(unsigned char *p, int arg)
{
    unsigned int i;
    unsigned char *ptr;

    if (arg == 2) {
        if (!(p[0x235] & 1)) {
            for (i = 0; i < 6; i++) {
                ptr = *(unsigned char **) (p + i * 4 + 0x2d8);
                if (ptr && ptr[0x2d8] != 0) {
                    func_ov009_022632c8(ptr);
                }
            }
        }
    }
    func_020033e4(p, arg);
}

int func_ov003_0221cd5c(UnkStruct_0221cd5c *p)
{
    unsigned int i;
    for (i = 0; i < 6; i++) {
        p->arr[i] = 0;
    }
    return 1;
}

void func_ov003_0221cd54(void *argument0)
{
    func_ov009_02264c10(argument0);
}

void func_ov003_0221cd4c(void *argument0)
{
    func_ov009_02264be0(argument0);
}

void func_ov003_0221cd44(void *argument0)
{
    func_ov009_02264b64(argument0);
}
