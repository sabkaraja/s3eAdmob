/*
Generic implementation of the s3eAdmob extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eAdmob_internal.h"
s3eResult s3eAdmobInit()
{
    //Add any generic initialisation code here
    return s3eAdmobInit_platform();
}

void s3eAdmobTerminate()
{
    //Add any generic termination code here
    s3eAdmobTerminate_platform();
}

s3eResult s3eAdmobStart(const char* pub_id, int ad_type, int orientation, int x, int y)
{
	return s3eAdmobStart_platform(pub_id, ad_type, orientation, x, y);
}

s3eResult s3eAdmobResize(int ad_type)
{
	return s3eAdmobResize_platform(ad_type);
}

s3eResult s3eAdmobShow()
{
	return s3eAdmobShow_platform();
}

s3eResult s3eAdmobRefresh()
{
	return s3eAdmobRefresh_platform();
}

s3eResult s3eAdmobHide()
{
	return s3eAdmobHide_platform();
}

s3eResult s3eAdmobMove(int orientation, int x, int y)
{
	return s3eAdmobMove_platform(orientation, x, y);
}

s3eResult s3eAdmobShowInterstitial(const char* med_id)
{
	return s3eAdmobShowInterstitial_platform(med_id);
}

s3eResult s3eAdmobShowSplash(const char* med_id)
{
	return s3eAdmobShowSplash_platform(med_id);
}
