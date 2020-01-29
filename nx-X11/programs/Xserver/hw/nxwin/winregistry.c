/*
 *Copyright (C) 1994-2000 The XFree86 Project, Inc. All Rights Reserved.
 *
 *Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 *"Software"), to deal in the Software without restriction, including
 *without limitation the rights to use, copy, modify, merge, publish,
 *distribute, sublicense, and/or sell copies of the Software, and to
 *permit persons to whom the Software is furnished to do so, subject to
 *the following conditions:
 *
 *The above copyright notice and this permission notice shall be
 *included in all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *NONINFRINGEMENT. IN NO EVENT SHALL THE XFREE86 PROJECT BE LIABLE FOR
 *ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 *CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *Except as contained in this notice, the name of the XFree86 Project
 *shall not be used in advertising or otherwise to promote the sale, use
 *or other dealings in this Software without prior written authorization
 *from the XFree86 Project.
 *
 * Authors:	Harold L Hunt II
 */
/* $XFree86: xc/programs/Xserver/hw/xwin/winregistry.c,v 1.1 2002/07/05 09:19:26 alanh Exp $ */

/**************************************************************************/
/*                                                                        */
/* Copyright (c) 2001,2006 NoMachine, http://www.nomachine.com.           */
/*                                                                        */
/* NXPROXY, NX protocol compression and NX extensions to this software    */
/* are copyright of NoMachine. Redistribution and use of the present      */
/* software is allowed according to terms specified in the file LICENSE   */
/* which comes in the source distribution.                                */
/*                                                                        */
/* Check http://www.nomachine.com/licensing.html for applicability.       */
/*                                                                        */
/* NX and NoMachine are trademarks of Medialogic S.p.A.                   */
/*                                                                        */
/* All rights reserved.                                                   */
/*                                                                        */
/**************************************************************************/

#include "win.h"


DWORD
winGetRegistryDWORD (HKEY hkey, char *pszRegistryKey)
{
  HKEY		hkResult;
  DWORD		dwDisposition;

  RegCreateKeyEx (hkey,
		  pszRegistryKey,
		  0,
		  '\0',
		  REG_OPTION_NON_VOLATILE,
		  KEY_READ,
		  NULL,
		  &hkResult,
		  &dwDisposition);

  if (dwDisposition == REG_CREATED_NEW_KEY)
    {
      ErrorF ("winGetRegistryDWORD - Created new key: %s\n", pszRegistryKey);
    }
  else if (dwDisposition == REG_OPENED_EXISTING_KEY)
    {
      ErrorF ("winGetRegistryDWORD - Opened existing key: %s\n",
	      pszRegistryKey);
    }

  /* Free the registry key handle */
  RegCloseKey (hkResult);
  hkResult = NULL;

  return 0;
}
