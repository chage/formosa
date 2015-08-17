/*
  see mode in struct user_info in struct.h
  enum mode declare in modes.h
*/

#include <sys/types.h>
#include <stdio.h>
#include "bbsconfig.h"
#include "struct.h"
#include "modes.h"
#include "libproto.h"

static char * ModeType[] = {

	/* MMENU */ "�D���",
	/* XMENU */ "�u����",
/*
 GMENU "�T�ֳ�",
*/
	/* ADMIN */ "�޲z��",
	/* BOARDS_MENU */ "�ݪO���",
	/* CLASS_MENU */ "�������",
	/* MAIL */ "�H����",
	/* READING */ "Ū�G�i",
	/* POSTING */ "�K�G�i",
	/* MODIFY */ "�ק�峹",
	/* RMAIL */ "Ū�H",
	/* SMAIL */ "�H�H",
	/* TMENU */ "�͸ܿ��",
	/* TALK */ "���",
	/* PAGE */ "�I��a",
	/* LUSERS */ "�d�u�W�H",
	/* LFRIENDS */ "�ݦѪB��",

	/* CHATROOM */ "��ѫ�",
	/* CHATROOM2 for nsysubbs */ "���߯���",
#if 0
	/* IRCCHAT */ "�ꤺ��Ѽs��",
	/* LOCALIRC */ "�󯸲�Ѽs��",
#endif
	/* SENDMSG */ "�e�T��",
/*
	ULDL "����",
*/
	/* QUERY */ "�d�߬Y�H",
	/* SELECT */ "��ݪO",
	/* EDITSIG */ "�sñ�W��",
	/* EDITPLAN */ "�s�W����",
	/* OVERRIDE */ "�s�n�ͦW��",
	/* BLACKLIST */ "�s�a�H�W��",
	/* LOGIN */ "ñ�줤",

	/* LAUSERS */ "�d�����H",
/*
	MONITOR "�ʬݤ�",
*/
	/* CLIENT */ "�D�q���\\����",
	/* WEBBBS */ "Web-BBS",
/*
   NEW "�s�ϥΪ̵��U",
 */
	/* VOTING */ "�벼��",
	/* EDITBMWEL */ "�s�i�O�e��",
	/* UNDEFINE */ "���w�q"
};


char *
modestring(upent, complete)
USER_INFO *upent;
int complete;
{
	static char modestr[30];
	register int mode = upent->mode;

#if 1
	if (mode > 31)
		return ModeType[31];
#endif
	if (complete)
	{
		/* user complain: SENDMESG �����O���p�� :) */
		if ((mode == TALK || mode == PAGE || mode == QUERY
			/*|| mode == SENDMSG*/) && upent->destid[0])
		{
			sprintf(modestr, "%s '%s'", ModeType[mode], upent->destid);
		}
		else if (mode == CHATROOM
#ifdef NSYSUBBS1
		          || mode == CHATROOM2
#endif
		          )
		{
			sprintf(modestr, "%s '%s'", ModeType[mode], upent->chatid);
		}
		else
			return (ModeType[mode]);
		return modestr;
	}
	return (ModeType[mode]);
}
