
#include "bbs.h"


/*
  �ϥΪ̬O�_�i�ݨ��Y�O�s�b
*/
int can_see_board(BOARDHEADER *bhr, unsigned int userlevel)
{
	return !((bhr->brdtype & BRD_PRIVATE) && userlevel < bhr->level);
/*
obsolete
�b�O�D�n�ͦW�椺�~�ݱo���� ���ΪO
   if (bhr->level == INVISIBLE_BOARD_LEVEL
       && !can_override(bhr->owner, userid))
   {
        return 0;
   }
	return 1;
*/
}


#if	1
/***********************************************************
 *	check if userid in board access control list
 *
 *	return:
 *		0 if allow access
 *  by asuka
 *
 ************************************************************/
int check_board_acl(char *boardname, char *userid)
{
	FILE *fp;
	char access_file[PATHLEN], buffer[STRLEN];
/*
not need, STRLEN*3 still not always enough, right?
	char *buffer[STRLEN*3];
*/

	if(strlen(userid) == 0)
		return -1;

	setboardfile(access_file, boardname, ACL_REC);
	if((fp = fopen(access_file, "r")) == NULL)
		return -2;

	while(fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		strtok(buffer, " \r\n");
		if(strlen(buffer) == 0)
			continue;
		if(!strcmp(buffer, userid))
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);

	return -3;
}
#endif
