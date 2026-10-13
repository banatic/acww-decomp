/* func_ov003_0221cdcc @ 0x0221cdcc, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(int *p);
extern int _u32_div_f(int a, int b);
extern int data_ov003_0223c8bc;
extern int data_ov003_0223c8b8;
extern int data_ov003_0223c8c0;

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
