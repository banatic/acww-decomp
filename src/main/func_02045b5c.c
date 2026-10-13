/* func_02045b5c @ 0x02045b5c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
struct Entry {
    unsigned char type : 3;
    unsigned char : 5;
    unsigned char : 7;
    unsigned char flag : 1;
    unsigned char pad_02[6];
    unsigned char data[8];
};
extern struct Entry data_021c7884[];
void *func_02045b5c(int id)
{
    struct Entry *p;
    int i;
    void *result = 0;
    if (func_02073d90(data_020ccf94) == 0) {
        id = 0;
    }
    p = data_021c7884;
    for (i = 0; i < 20; i++) {
        if ((id == p->type) && p->flag) {
            result = (void *) p->data;
            break;
        }
        p++;
    }

    return result;
}
