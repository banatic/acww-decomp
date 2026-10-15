/* CTRDG_WriteAgbFlashSectorAsync @ 0x020ed6c4, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct CTRDGTaskInfo_tag;

typedef u32 (*CTRDG_TASK_FUNC)(struct CTRDGTaskInfo_tag *);

typedef struct CTRDGTaskInfo_tag {
    CTRDG_TASK_FUNC task;
    CTRDG_TASK_FUNC callback;
    u32 result;
    u8 *data;
    u8 *adr;
    u32 offset;
    u32 size;
    u8 *dst;
    u16 sec_num;
    u8 busy;
    u8 param[1];
} CTRDGTaskInfo;

extern void CTRDG_WriteAgbFlashSectorAsync(int index, char *buffer, unsigned int length);

extern const u16(*ctrdgi_fl_maxtime);

extern void (*CTRDGi_WriteAgbFlashSectorAsync)(int index, char *buffer, unsigned int length);

extern void (*CTRDGi_WriteAgbFlashSectorAsync)(int index, char *buffer, unsigned int length);

const u16(*ctrdgi_fl_maxtime);

void CTRDG_WriteAgbFlashSectorAsync(int index, char *buffer, unsigned int length)
{
    (*CTRDGi_WriteAgbFlashSectorAsync)(index, buffer, length);
}
