/* func_02094ffc @ 0x02094ffc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064294(void *p);
extern int memcmp(void *p1, void *p2, unsigned int size);

struct UnkStruct_02094ffc {
    unsigned short id;
    unsigned char tail[12];
};

extern struct UnkStruct_02094ffc data_021dc7aa;

int func_02094ffc(struct UnkStruct_02094ffc *p)
{
    int result = 2;
    if (func_02064294(p) != 0) {
        struct UnkStruct_02094ffc *q = &data_021dc7aa;
        if (p->id == q->id && memcmp(p->tail, q->tail, 0xc) == 0) {
            result = 0;
        } else {
            result = 1;
        }
    }
    return result;
}
