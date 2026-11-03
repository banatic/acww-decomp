/* turtle6_talk_2: 3 functions, module ov086
 * mwccarm 1.2/base -O4,s
 * func_ov086_02278ec8 @ 0x02278ec8, 0x18 bytes, Thumb
 * func_ov086_02278eb0 @ 0x02278eb0, 0x18 bytes, Thumb
 * func_ov086_02278e90 @ 0x02278e90, 0x20 bytes, Thumb
 */

typedef struct {
    void *unk_00;
} UnkStruct_02278eb0;

extern void *func_0202eb70(void *p);
extern unsigned char data_ov086_022792fc[];
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

void *func_ov086_02278ec8(void *p)
{
    func_0202eb70(p);
    *(unsigned int *) p = (unsigned int) data_ov086_022792fc;
    return p;
}

void *func_ov086_02278eb0(void *obj)
{
    ((UnkStruct_02278eb0 *) obj)->unk_00 = (void *) ((int *) data_ov086_022792fc);
    func_0202eb20(obj);
    return obj;
}

void *func_ov086_02278e90(void *obj)
{
    *((unsigned int *) obj) = (unsigned int) data_ov086_022792fc;
    func_0202eb20(obj);
    func_020edb3c(obj);
    return obj;
}
