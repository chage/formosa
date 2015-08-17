#include "bbs.h"
#include "bbsweb.h"
#include "log.h"
#include "bbswebproto.h"


extern POST_FILE *post_file;
#if 0
extern USER_REC *curuser;
#endif

int ParseKMP(char *cmd, REQUEST_REC *r)
{

	char kmp[STRLEN], proto[STRLEN], data[STRLEN], arg1[STRLEN], arg2[STRLEN], arg3[STRLEN], arg4[STRLEN];
	int result;
	*proto = *data = *arg1 = *arg2 = *arg3 = *arg4 = 0x00;

	sscanf(cmd, "%s\t%s\t%s\t%s\t%s\t%s",
		kmp, proto, arg1, arg2, arg3, arg4);

#if 0
	fprintf(fp_out, "[%s]\r\n", cmd);
	fprintf(fp_out, "arg1=%s, arg2=%s, arg3=%s, arg4=%s\r\n",
		arg1, arg2, arg3, arg4);
	fflush(fp_out);
#endif

	if(!strcmp(proto, "USERNEW"))
	{
		sprintf(data, "ID=%s&PASSWORD=%s&PASSWORD1=%s&NICKNAME=%s&EMAIL=%s",
			arg1, arg2, arg2, arg3, arg4);

		result = NewUser(data, &curuser);

		if(result != WEB_OK)
		{
			if(strstr(WEBBBS_ERROR_MESSAGE, "�b���w�s�b") != NULL)
				fprintf(fp_out, "622  �ϥΪ̱b���w�s�b\r\n");
			else
				fprintf(fp_out, "721  ���U����\r\n");
		}
		else
			fprintf(fp_out, "800  OK!!\r\n");
	}
	else if(!strcmp(proto, "USERQUERY"))
	{
		if (!get_passwd(&curuser, arg1))
		{
			bzero(&curuser, sizeof(USEREC));
			fprintf(fp_out, "621  �ϥΪ̱b�����s�b\r\n");
		}
		else
		{
			USER_INFO *quinf;
			char user_status[1024];

			if ((quinf = search_ulist(cmp_userid, curuser.userid)) && !(quinf->invisible))
			{
				sprintf(user_status, "�u�W���A: %s, �I��a: %s.",
					modestring(quinf, 1),
					(quinf->pager != PAGER_QUIET) ? MSG_ON : MSG_OFF);
			}
			else
				sprintf(user_status, "�ثe���b�u�W");

			fprintf(fp_out, "800  OK!!\r\n");
			fprintf(fp_out, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%s\t%s\r\n",
				curuser.userid,
				curuser.username,
				curuser.userlevel,
				curuser.ident,
				curuser.numlogins,
				curuser.numposts,
				(int)curuser.lastlogin,
				curuser.lasthost,
				user_status);
		}
	}
	else if(!strcmp(proto, "USERDATA"))
	{
		if(!get_passwd(&curuser, arg1))
			bzero(&curuser, sizeof(USEREC));
		if(CheckUserPassword(arg1, arg2)!=Correct)
			fprintf(fp_out, "724  �K�X���~\r\n");
		else
		{
			fprintf(fp_out, "800  OK!!\r\n");
			fprintf(fp_out, "%d\t%s\t%s\t%d\t%d\t%d\t%s\t%d\t%s\r\n",
				curuser.uid,
				curuser.userid,
				curuser.username,
				curuser.userlevel,
				curuser.numlogins,
				curuser.numposts,
				curuser.lasthost,
				curuser.lastctype,
				curuser.email);
		}
	}
	else if(!strcmp(proto, "USERPLAN"))
	{
		if (!get_passwd(&curuser, arg1))
		{
			bzero(&curuser, sizeof(USEREC));
			fprintf(fp_out, "621  �ϥΪ̱b�����s�b\r\n");
		}
		else
		{
			char userfile[PATHLEN];

			sethomefile(userfile, curuser.userid, UFNAME_PLANS);
			if(isfile(userfile))
			{
				fprintf(fp_out, "800  OK!!\r\n");
				ShowArticle(userfile, FALSE, FALSE);
			}
			else
			{
				fprintf(fp_out, "761  �ϥΪ̵L�W����\r\n");
			}
		}
	}
	else if(!strcmp(proto, "USERLIST"))
	{
		int start = 0, end = 0;

		if(*arg1)
			start = atoi(arg1);
		if(*arg2)
			end = atoi(arg2);

	#if 0
		fprintf(fp_out, "%p %p", post_file, &post_file);
		fflush(fp_out);
	#else
		post_file->list_start = start;
		post_file->list_end = end;
		ShowUserList("KMP", post_file);
	#endif
	}
#if 0
	else if(!strcmp(proto, "USERLOGIN"))
	{
		result = user_login(&cutmp, &curuser, CTYPE_WEBBBS, arg1, arg2,
			       r->fromhost);
		if (result == ULOGIN_OK)
		{
			memcpy(&uinfo, cutmp, sizeof(USER_INFO));
			break;
		}
		else if (result == ULOGIN_PASSFAIL)
		{
			outs(_msg_formosa_27);
			continue;
		}
		outs(_msg_formosa_44);


	}
#endif

	return WEB_OK;

}
