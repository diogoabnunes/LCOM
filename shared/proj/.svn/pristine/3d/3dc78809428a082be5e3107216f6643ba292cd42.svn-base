PROG=proj

SRCS = proj.c game.c state_machine.c dot.c xpms.c cards.c video.c mouse.c keyboard.c timer.c utils.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
