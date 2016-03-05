/**
* @brief
*		Find errors and decrease probability of getting errors of the same kind in the future
*		This piece of code won't compile and it doesn't describe an entire algorithm: just part of some page storage
*
* @author
*		AnnaM
*/

/// amount of guessed bugs 8

// 1bug
//#include <Windows.h>
#include <stdio.h>

enum PAGE_COLOR {
    PG_COLOR_GREEN, /* page may be released without high overhead */
    PG_COLOR_YELLOW, /* nice to have */
    PG_COLOR_RED, /* page is actively used */
    PG_TOTAL_COLORS
};


/**
 * UINT Key of a page in hash-table (prepared from color and address)
 */
union PageKey {
    struct {
        UINT cColor: 8;
        UINT cAddr: 24;
    };

    UINT uKey;
};


/* Prepare from 2 chars the key of the same configuration as in PageKey */
#define CALC_PAGE_KEY(Addr, Color)    (  (Color) + ((Addr) << 8)))


/**
 * Descriptor of a single guest physical page
 */
struct PageDesc {
    PageKey uKey;

    /* list support */
    PageDesc * next, * prev;
};

#define PAGE_INIT(Desc, Addr, Color)              \
    do{                                               \
        (Desc).uKey = CALC_PAGE_KEY( Addr, Color ); \
        (Desc).next = (Desc).prev = NULL;           \
    }while(0)


/* storage for pages of all colors */
static PageDesc * PageStrg[3];

void PageStrgInit() {
    memset(PageStrg, 0, sizeof(*PageStrg) * PG_TOTAL_COLORS);
}

PageDesc * PageFind(void * ptr, unsigned char color) {
    if (color > PG_TOTAL_COLORS)
        return NULL;
    for (PageDesc * Pg = PageStrg[color]; Pg; Pg = Pg->next)
        if (Pg->uKey == CALC_PAGE_KEY((UINT) ptr, color))
    return Pg;
    return NULL;
}

PageDesc * PageReclaim(UINT cnt) {
    UINT color = 0;
    PageDesc * Pg = PageStrg[0];
    while (cnt) {
        if (Pg == NULL) {
            color++;
            Pg = PageStrg[color];
        }
        Pg = Pg->next;
        PageRemove(PageStrg[color]);
        cnt--;
    }
    return Pg
}

PageDesc * PageInit(void * ptr, UINT color) {
    try {
        PageDesc * pg = new PageDesc;
        if (pg)
            PAGE_INIT(*pg, ptr, color);
        else
            printf("Allocation has failed\n");
        return pg;
    }
    catch (bad_alloc) {
        printf("Bad allocation\n");
        return NULL;
    }
    return NULL;
}

/**
 * Print all mapped pages
 */
void PageDump() {
    UINT color = 0;
#define PG_COLOR_NAME(clr) #clr
    char * PgColorName[] =
    {
    PG_COLOR_NAME(PG_COLOR_GREEN),
    PG_COLOR_NAME(PG_COLOR_YELLOW),
    PG_COLOR_NAME(PG_COLOR_RED)
    };

    while (color <= PG_COLOR_RED) {
        printf("PgStrg[(%s) %u] ********** \n", PgColorName[color], color);
        for (PageDesc * Pg = PageStrg[color++]; Pg != NULL; Pg = Pg->next) {
            if (Pg->uAddr == NULL)
                continue;

            printf("Pg :Key = 0x%x, addr %p\n", Pg->uKey, Pg->uAddr);
        }
    }
#undef PG_COLOR_NAME
}
