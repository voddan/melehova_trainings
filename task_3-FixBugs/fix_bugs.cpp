/**
* @brief
*		Find errors and decrease probability of getting errors of the same kind in the future
*		This piece of code won't compile and it doesn't describe an entire algorithm: just part of some page storage
*
* @author
*		AnnaM
*/

#include "Windows.h"
#include <stdio.h>

#include "helper.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
enum PAGE_COLOR {
    /*fixed: initial enum value*/
    PG_COLOR_GREEN, /* page may be released without high overhead */
    PG_COLOR_YELLOW, /* nice to have */
    PG_COLOR_RED    /* page is actively used */
};


/**
 * UINT Key of a page in hash-table (prepared from color and address)
 */
union PageKey {
    struct {
        CHAR cColor: 8;
        UINT cAddr: 24;
    };

    UINT uKey;
};


/* Prepare from 2 chars the key of the same configuration as in PageKey */
/*fixed: braces around <<*/
#define CALC_PAGE_KEY(Addr, Color)    (  (Color) + ((UINT) Addr << 8) )


/**
 * Descriptor of a single guest physical page
 */
struct PageDesc {
    PageKey uKey;

    /* list support */
    PageDesc * next, * prev;

    /*fixed: missing pointer*/
    void * uAddr;
};

#define PAGE_INIT(Desc, Addr, Color)              \
    {                                               \
        (Desc).uKey.uKey = CALC_PAGE_KEY( Addr, Color ); \
        (Desc).next = (Desc).prev = NULL;           \
    }


/* storage for pages of all colors */
static PageDesc * PageStrg[3];

void PageStrgInit() {
    /*fixed: pointer to an array*/
    memset(PageStrg, 0, sizeof(PageStrg));
}

PageDesc * PageFind(void * ptr, char color) {
    /*fixed: semicolon after for*/
    for (PageDesc * Pg = PageStrg[color]; Pg; Pg = Pg->next)
        /*fixed: added uKey.uKey*/
        if (Pg->uKey.uKey == CALC_PAGE_KEY(ptr, color))
            return Pg;
    return NULL;
}

/*fixed: added PageRemove declaration*/
void PageRemove(PageDesc * pdp);

PageDesc * PageReclaim(UINT cnt) {
    UINT color = 0;
    /*fixed: init Pg*/
    PageDesc * Pg = PageStrg[color];
    /*todo: use for-loop*/
    while (cnt) {
        Pg = Pg->next;
        PageRemove(PageStrg[color]);
        cnt--;
        if (Pg == NULL) {
            color++;
            Pg = PageStrg[color];
        }
    }
    /*fixed: added return statement*/
    return Pg;
}

PageDesc * PageInit(void * ptr, UINT color) {
    PageDesc * pg = new PageDesc;
    /*fixed: semicolon after if*/
    /*todo: delete if - new operator ALWAYS returns an object (or throws an exception)*/
    if (pg)
        /*fixed: replaced & with **/
    PAGE_INIT(*pg, ptr, color)
    else
        printf("Allocation has failed\n");

    return pg;
}

/**
 * Print all mapped pages
 */
void PageDump() {
    UINT color = 0;
#define PG_COLOR_NAME(clr) #clr
    /*todo: autocasting ("" -> (char*)) is deprecated*/
    char * PgColorName[] =
    {
    (char *) PG_COLOR_NAME(PG_COLOR_RED),
    (char *) PG_COLOR_NAME(PG_COLOR_YELLOW),
    (char *) PG_COLOR_NAME(PG_COLOR_GREEN)
    };

    while (color <= PG_COLOR_RED) {
        /*fixed: swapped the printf args*/
        printf("PgStrg[(%s) %u] ********** \n", PgColorName[color], color);
        /*fixed: replaced ++color with color++ */
        for (PageDesc * Pg = PageStrg[color++]; Pg != NULL; Pg = Pg->next) {
            /*fixed: replaced = with == in condition */
            if (Pg->uAddr == NULL)
                continue;

            printf("Pg :Key = 0x%x, addr %p\n", Pg->uKey, Pg->uAddr);
        }
    }
#undef PG_COLOR_NAME
}

#pragma clang diagnostic pop