/*
 * windows-specific implementation of the s3eAdmob extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eAdmob_internal.h"

s3eResult s3eAdmobInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eAdmobTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult s3eAdmobStart_platform(const char* pub_id, int ad_type, int orientation, int x, int y)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobResize_platform(int ad_type)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShow_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobRefresh_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobHide_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobMove_platform(int orientation, int x, int y)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShowInterstitial_platform(const char* med_id)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdmobShowSplash_platform(const char* med_id)
{
    return S3E_RESULT_ERROR;
}
