
#include "bbs.h"
#include "csbbs.h"


int
get_user_file(keyword)
char *keyword;
{
	char buf[PATHLEN];

	sethomefile(buf, curuser.userid, keyword);
	if (get_num_records(buf, sizeof(char)) == 0)
		return -1;
	SendArticle(buf, TRUE);
	return 0;
}


void
send_user_file(keyword)
char *keyword;
{
	char buf[PATHLEN], fname[PATHLEN];

#ifdef GUEST
	if (!strcmp(curuser.userid, GUEST))
	{			/* �p�G�ϥΪ̬� guest �n�� */
		RespondProtocol(WORK_ERROR);
		return;
	}
#endif

	sethomefile(buf, curuser.userid, keyword);
	sprintf(fname, "tmp/_csbbs.%s.%ld", curuser.userid, time(0));
	/* mycp will delete destination file first */
	if (!RecvArticle(fname, FALSE, NULL, NULL))
	{
		if (!mycp(fname, buf))
		{
			unlink(fname);		/* lthuang */
			RespondProtocol(OK_CMD);
			return;
		}
	}
	unlink(fname);	/* lthuang */
	RespondProtocol(WORK_ERROR);
}


void
kill_user_file(keyword)
char *keyword;
{
	char buf[PATHLEN];

	sethomefile(buf, curuser.userid, keyword);
	if (isfile(buf) && unlink(buf) == -1)
		RespondProtocol(WORK_ERROR);
	else
		RespondProtocol(OK_CMD);

}


/***********************************************************
*		PLANGET
*			���o�{�buser���W����
************************************************************/
DoGetPlan()
{
	if (get_user_file(UFNAME_PLANS) < 0)
		RespondProtocol(NO_PLAN);
}


/************************************************************
*		PLANKILL
*			�R��user�W����
*************************************************************/
DoKillPlan()
{
	kill_user_file(UFNAME_PLANS);
}


/**************************************************************
*		PLANPUT
*			�e�XUSER���W����
***************************************************************/
DoSendPlan()
{
	send_user_file(UFNAME_PLANS);
}


/**************************************************************
*		SIGNGET
*			���o�ϥΪ�ñ�W��
***************************************************************/
DoGetSign()
{
	if (get_user_file(UFNAME_SIGNATURES) < 0)
		RespondProtocol(NO_SIGN);
}


/*************************************************************
*		SIGNKILL
*			�R���ϥΪ�ñ�W��
**************************************************************/
DoKillSign()
{
	kill_user_file(UFNAME_SIGNATURES);
}


/****************************************************************
*		SIGNPUT
*			�e�XUSERñ�W��
*****************************************************************/
DoSendSign()
{
	send_user_file(UFNAME_SIGNATURES);
}


/*************************************************************
*		CHGPASSWD newpass
*			�ק�ϥΪ̱K�X
**************************************************************/
DoChangePassword()
{
	char *passbuf;
	char *pass;
	extern char *genpasswd();
	char npass[8];

#ifdef GUEST
	if (!strcmp(curuser.userid, GUEST))
	{			/* �p�G�ϥΪ̬� guest �n�� */
		RespondProtocol(WORK_ERROR);
		return;
	}
#endif

	/* Get_para_string() is buggy, comment by lthuang */
	passbuf = Get_para_string(1);
	if (passbuf == NULL || passbuf[0] == '\0')
	{
		RespondProtocol(SYNTAX_ERROR);
		return;
	}
	passbuf[8] = '\0';
	xstrncpy(npass, passbuf, sizeof(npass));
	chk_str2(passbuf);
	if (strcmp(passbuf, npass))	/* if new password contains illeagel chars */
	{
		RespondProtocol(WORK_ERROR);
		return;
	}

	pass = genpasswd(passbuf);
	strncpy(curuser.passwd, pass, PASSLEN);
/*
update_passwd only when logout
	update_passwd(&curuser);
*/
/*
   update_user_passfile(&curuser);
 */
	RespondProtocol(OK_CMD);
}


/******************************************************************
*		USERGET
*			���o�ϥΪ̸��
*******************************************************************/
DoGetUserData()
{
	RespondProtocol(OK_CMD);

	inet_printf("%s\t%s\t",
	        (curuser.username[0]) ? curuser.username : "#",
	        (curuser.email[0]) ? curuser.email : "#");
	inet_printf("%s\t%d\t%d\t%d\t%d\t",
		    /*term_type*/ "#", curuser.numlogins, curuser.numposts,
		    curuser.userlevel, curuser.uid);
	inet_printf("%s\t%s\t%c\t",
		    curuser.lasthost, Ctime(&curuser.lastlogin),
		    (curuser.pager) ? '1' : '0');	/* pager flag */
	inet_printf("%c\t%c\r\n", curuser.ident + '0',
		    (curuser.flags[0] & FORWARD_FLAG) ? '1' : '0');
}


/******************************************************************
*		CHGNAME name
*			�ק�USER�ʺ�
*******************************************************************/
DoChangeUserName()
{
	char *name;

#ifdef GUEST
	if (!strcmp(curuser.userid, GUEST))
	{			/* �p�G�ϥΪ̬� guest �n�� */
		RespondProtocol(WORK_ERROR);
		return;
	}
#endif

	name = Get_para_string(1);
	if (name != NULL)
	{
		strcpy(curuser.username, name);
		chk_str2(curuser.username);
	}
	else
		curuser.username[0] = '\0';

/*
update_passwd only when logout
	update_passwd(&curuser);
*/
/*
   update_user_passfile(&curuser);
 */
	RespondProtocol(OK_CMD);
}


/************************************************************
*		CHGMAIL
*			�ק�E-mail�b��
*************************************************************/
DoChangeEMail()
{
	char *email;

#ifdef GUEST
	if (!strcmp(curuser.userid, GUEST))
	{			/* �p�G�ϥΪ̬� guest �n�� */
		RespondProtocol(WORK_ERROR);
		return;
	}
#endif

	email = Get_para_string(1);
	if (!email)
	{
		RespondProtocol(SYNTAX_ERROR);
		return;
	}
	chk_str2(email);

	strcpy(curuser.email, email);
/*
update_passwd only when logout
	update_passwd(&curuser);
*/
/*
   update_user_passfile(&curuser);
 */
	RespondProtocol(OK_CMD);
}
