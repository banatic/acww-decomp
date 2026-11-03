/* music_queue_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02035638 @ 0x02035638, 0x14 bytes, Thumb
 * func_02035624 @ 0x02035624, 0x14 bytes, Thumb
 * func_02035610 @ 0x02035610, 0x14 bytes, Thumb
 */

extern void func_02035148(void *param1, void *param2, int param3);
extern unsigned char data_021c526c[];
extern void func_02035170(void *a, int b);

void func_02035638(void *param)
{
    void *r0;
    void *r1;
    int r2;

    r1 = param;
    r0 = *(void **) data_021c526c;
    r2 = 0;
    func_02035148(r0, r1, r2);
}

void func_02035624(int arg)
{
    func_02035170((void *) (*(int *) data_021c526c), arg);
}

void func_02035610(int arg0)
{
    func_02035148((void *) ((*(int *) data_021c526c)), (void *) arg0, 1);
}
