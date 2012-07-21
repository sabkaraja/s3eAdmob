/*
 * Internal header for the s3eAdmob extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EADMOB_INTERNAL_H
#define S3EADMOB_INTERNAL_H

#include "s3eTypes.h"
#include "s3eAdmob.h"
#include "s3eAdmob_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eAdmobInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eAdmobInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eAdmobTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eAdmobTerminate_platform();
s3eResult s3eAdmobStart_platform(const char* pub_id, int ad_type, int orientation, int x, int y);

s3eResult s3eAdmobResize_platform(int ad_type);

s3eResult s3eAdmobShow_platform();

s3eResult s3eAdmobRefresh_platform();

s3eResult s3eAdmobHide_platform();

s3eResult s3eAdmobMove_platform(int orientation, int x, int y);

s3eResult s3eAdmobShowInterstitial_platform(const char* med_id);

s3eResult s3eAdmobShowSplash_platform(const char* med_id);


#endif /* !S3EADMOB_INTERNAL_H */