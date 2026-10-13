/* func_020be0f8 @ 0x020be0f8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Record {
    int id;
    unsigned char pad_04[0x70];
} Record;
int func_020be0f8(Record *records, int param1, int param2)
{
    int val;
    int result = 0x3c;
    if (param2 != 0x3c) {
        if (records[param2].id == 0xd) {
            result = param2;
        }
    } else if (param1 == 9) {
        Record *p = (Record *) (((char *) records) + 0x14d8);
        int i;
        i = 0x2e;
        while (i <= 0x3a) {
            if (p->id == 0xd) {
                result = i;
                break;
            }
            i++;
            p = (Record *) (((char *) p) + 0x74);
        }

    } else {
        int j;
        Record *q = records;
        if ((*((int *) (((char *) records) + 0x2f14))) < 0x1e) {
            for (j = 0; j < 0x1e; j++) {
                val = q->id == 0xd;
                if (val) {
                    result = j;
                    break;
                }
                q = (Record *) (((char *) q) + 0x74);
            }
        }
    }
    return result;
}
