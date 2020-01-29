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
 * Authors:	Dakshinamurthy Karra
 *		Suhaib M Siddiqi
 *		Peter Busch
 *		Harold L Hunt II
 */
/* $XFree86: xc/programs/Xserver/hw/xwin/wincursor.c,v 1.5 2002/07/05 09:19:26 alanh Exp $ */

/**************************************************************************/
/*                                                                        */
/* Copyright (c) 2001, 2009 NoMachine, http://www.nomachine.com.          */
/*                                                                        */
/* NXWIN, NX protocol compression and NX extensions to this software      */
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

miPointerScreenFuncRec g_winPointerCursorFuncs =
{
  winCursorOffScreen,
  winCrossScreen,
  winPointerWarpCursor
};


void
winPointerWarpCursor (ScreenPtr pScreen, int x, int y)
{
  winScreenPriv(pScreen);
  RECT			rcClient;

  /* Only update the Windows cursor position if we are active */
  if (pScreenPriv->hwndScreen == GetForegroundWindow ())
    {
      /* Get the client area coordinates */
      GetClientRect (pScreenPriv->hwndScreen, &rcClient);
      
      /* Translate the client area coords to screen coords */
      MapWindowPoints (pScreenPriv->hwndScreen,
		       HWND_DESKTOP,
		       (LPPOINT)&rcClient,
		       2);
      
      /* 
       * Update the Windows cursor position so that we don't
       * immediately warp back to the current position.
       */
      SetCursorPos (rcClient.left + x, rcClient.top + y);
    }

  /* Call the mi warp procedure to do the actual warping in X. */
  miPointerWarpCursor (pScreen, x, y);
}

Bool
winCursorOffScreen (ScreenPtr *ppScreen, int *x, int *y)
{
  return FALSE;
}

void
winCrossScreen (ScreenPtr pScreen, Bool fEntering)
{
}

#ifndef NXWIN_OLD_CURSORS

#include "cursorstr.h"

#define WIN98ORGREATER (nxwinOsVersionInfo.dwPlatformId == 1 && \
                          nxwinOsVersionInfo.dwMajorVersion == 4 && \
                          nxwinOsVersionInfo.dwMinorVersion >= 10)

#define WIN2KORGREATER (nxwinOsVersionInfo.dwPlatformId == 2 && \
                          nxwinOsVersionInfo.dwMajorVersion >= 5)

int nxwinOldCursors = 0;
int nxwinCursorWidth;
int nxwinCursorHeight;

int nxwinAlphaCaps;

OSVERSIONINFO nxwinOsVersionInfo = {0};
  
HCURSOR nxwinCurrentCursor = NULL;


unsigned char nxwinFlipChar[256] =
{
    0, 128,  64, 192,  32, 160,  96, 224,
   16, 144,  80, 208,  48, 176, 112, 240,
    8, 136,  72, 200,  40, 168, 104, 232,
   24, 152,  88, 216,  56, 184, 120, 248,
    4, 132,  68, 196,  36, 164, 100, 228,
   20, 148,  84, 212,  52, 180, 116, 244,
   12, 140,  76, 204,  44, 172, 108, 236,
   28, 156,  92, 220,  60, 188, 124, 252,
    2, 130,  66, 194,  34, 162,  98, 226,
   18, 146,  82, 210,  50, 178, 114, 242,
   10, 138,  74, 202,  42, 170, 106, 234,
   26, 154,  90, 218,  58, 186, 122, 250,
    6, 134,  70, 198,  38, 166, 102, 230,
   22, 150,  86, 214,  54, 182, 118, 246,
   14, 142,  78, 206,  46, 174, 110, 238,
   30, 158,  94, 222,  62, 190, 126, 254,
    1, 129,  65, 193,  33, 161,  97, 225,
   17, 145,  81, 209,  49, 177, 113, 241,
    9, 137,  73, 201,  41, 169, 105, 233,
   25, 153,  89, 217,  57, 185, 121, 249,
    5, 133,  69, 197,  37, 165, 101, 229,
   21, 149,  85, 213,  53, 181, 117, 245,
   13, 141,  77, 205,  45, 173, 109, 237,
   29, 157,  93, 221,  61, 189, 125, 253,
    3, 131,  67, 195,  35, 163,  99, 227,
   19, 147,  83, 211,  51, 179, 115, 243,
   11, 139,  75, 203,  43, 171, 107, 235,
   27, 155,  91, 219,  59, 187, 123, 251,
    7, 135,  71, 199,  39, 167, 103, 231,
   23, 151,  87, 215,  55, 183, 119, 247,
   15, 143,  79, 207,  47, 175, 111, 239,
   31, 159,  95, 223,  63, 191, 127, 255
};



typedef struct {
  PixmapPtr sourceBits;
  PixmapPtr maskBits;
  #ifdef ARGB_CURSOR
  CARD32 *argb;
  #endif
  
  HCURSOR cursor;
} nxwinPrivCursor;

#define nxwinCursorPriv(pCursor, pScreen) \
  ((nxwinPrivCursor *) ((pCursor) -> devPriv[pScreen->myNum]))

static int nxwinRealizeCursor(ScreenPtr pScreen, CursorPtr pCursor)
{
  nxwinPrivCursor *pPriv;
  GCPtr pGC;
  XID  gcvals[3];
  int n;
  int i;
  unsigned char *xorMask;
  unsigned char *andMask;
  PixmapPtr pTempAnd;
  PixmapPtr pTempXor;
  xRectangle backrect;

  pCursor->devPriv[pScreen->myNum] = xalloc(sizeof(nxwinPrivCursor));
  pPriv = nxwinCursorPriv(pCursor, pScreen);


  pPriv->sourceBits = NULL;
  pPriv->maskBits = NULL;

#ifdef ARGB_CURSOR

#define MIN(a, b) ((a) < (b) ? (a) : (b))

  pPriv->argb = NULL;

  if (pCursor->bits->argb != NULL)
  {
    int remote = GetSystemMetrics(SM_REMOTESESSION);

    if ((WIN2KORGREATER || WIN98ORGREATER) && remote == 0)
    {
      DWORD width, height;
      BITMAPV5HEADER bhead;
      HBITMAP pBitmap;
      void *pBits;
      DWORD x,y;
      DWORD *pPixel;
      CARD32 *pCursorBits;
      HBITMAP pMask;
      ICONINFO iconinfo;

      width  = nxwinCursorWidth;
      height = nxwinCursorHeight;

      ZeroMemory(&bhead,sizeof(BITMAPV5HEADER));
      bhead.bV5Size           = sizeof(BITMAPV5HEADER);
      bhead.bV5Width           = width;
      bhead.bV5Height          = -height;
      bhead.bV5Planes = 1;
      bhead.bV5BitCount = 32;
      bhead.bV5Compression = BI_BITFIELDS;

      bhead.bV5RedMask   =  0x00FF0000;
      bhead.bV5GreenMask =  0x0000FF00;
      bhead.bV5BlueMask  =  0x000000FF;
      bhead.bV5AlphaMask =  0xFF000000; 

      HDC hdc;
      hdc = GetDC(NULL);


      pBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bhead, DIB_RGB_COLORS, 
          (void **)&pBits, NULL, (DWORD)0);

      ReleaseDC(NULL,hdc);

      pPixel = (DWORD *)pBits;
      pCursorBits = pCursor->bits->argb;


      for (y = 0; y < MIN(height, pCursor->bits->height) ; y++)
      {
        for (x = 0; x < MIN(width, pCursor->bits->width); x++)
        {
          *(pPixel + y * width + x) =
              *(pCursor->bits->argb + y * pCursor->bits->width + x);
        }
      }

      pMask = CreateBitmap(width, height, 1, 1, NULL);

      iconinfo.fIcon = 0;  /* Create a cursor. */
      iconinfo.xHotspot = pCursor->bits->xhot;
      iconinfo.yHotspot = pCursor->bits->yhot;
      iconinfo.hbmMask = pMask;
      iconinfo.hbmColor = pBitmap;

      nxwinCursorPriv(pCursor, pScreen)->cursor = CreateIconIndirect(&iconinfo);

      DeleteObject(pBitmap);          
      DeleteObject(pMask); 
      
      if (nxwinCursorPriv(pCursor, pScreen)->cursor == NULL)
      {
        ErrorF("nxwinRealizeCursor: Failed to create ARGB cursor.\n");

        goto ColorCursorError;
      }

      #ifdef DEBUG
      ErrorF("nxwinRealizeCursor: Created ARGB cursor with handle [%p].\n",
                 nxwinCursorPriv(pCursor, pScreen)->cursor);
      #endif

      pPriv->argb = pCursor->bits->argb;

      return 1;
    }
    else
    {
      HDC dc = GetDC(NULL);
      HDC andDC = CreateCompatibleDC(dc);
      HDC xorDC = CreateCompatibleDC(dc);

      HBITMAP andBitmap;
      HBITMAP xorBitmap;
      HBITMAP andOldBitmap;
      HBITMAP xorOldBitmap;

      int x, y;
      CARD32 *argb;

      ICONINFO iconinfo = {0};

      andBitmap = CreateCompatibleBitmap(dc, pCursor->bits->width,
                      pCursor->bits->height);

      xorBitmap = CreateCompatibleBitmap(dc, pCursor->bits->width,
                      pCursor->bits->height);

      andOldBitmap = (HBITMAP) SelectObject(andDC, andBitmap);
      xorOldBitmap = (HBITMAP) SelectObject(xorDC, xorBitmap);

      argb = pCursor->bits->argb;

      for (y = 0; y < pCursor->bits->height; y++)
      {
        for (x = 0; x < pCursor->bits->width; x++)
        {
          if (((unsigned char*)argb)[3] > 127)
          {
            SetPixelV(xorDC, x, y, RGB(((char*)argb)[2], ((char*)argb)[1],
                         ((char*)argb)[0]));

            SetPixelV(andDC, x, y, RGB(0, 0, 0));
          }
          else
          {
            SetPixel(xorDC, x, y, RGB(0, 0, 0));
            SetPixel(andDC, x, y, RGB(255, 255, 255));
          }

          argb++;
        }
      }

      SelectObject(andDC, andOldBitmap);
      SelectObject(xorDC, xorOldBitmap);


      DeleteDC(andDC);
      DeleteDC(xorDC);

      ReleaseDC(NULL, dc);

      iconinfo.fIcon          = 0;
      iconinfo.xHotspot       = pCursor->bits->xhot;
      iconinfo.yHotspot       = pCursor->bits->yhot;
      iconinfo.hbmMask        = andBitmap;
      iconinfo.hbmColor       = xorBitmap;

      nxwinCursorPriv(pCursor, pScreen)->cursor =
          CreateIconIndirect(&iconinfo);

      DeleteObject(andBitmap);
      DeleteObject(xorBitmap);

      if (nxwinCursorPriv(pCursor, pScreen)->cursor == NULL)
      {
        ErrorF("nxwinRealizeCursor: Failed to create color cursor.\n");

        goto ColorCursorError;
      }

      #ifdef DEBUG
      ErrorF("nxwinRealizeCursor: Created color cursor with handle [%p].\n",
                  nxwinCursorPriv(pCursor, pScreen)->cursor);
      #endif

      pPriv->argb = pCursor->bits->argb;

      return 1;
    }
  }

ColorCursorError:

#endif

  pPriv->sourceBits = (*pScreen->CreatePixmap)
                          (pScreen, pCursor->bits->width,
                              pCursor->bits->height, 1);

  if (pPriv->sourceBits == NULL)
  {
    xfree (pPriv);

    return 0;
  }

  pPriv->maskBits = (*pScreen->CreatePixmap)
                        (pScreen, pCursor->bits->width,
                            pCursor->bits->height, 1);

  if (pPriv->maskBits == NULL)
  {
    (*pScreen->DestroyPixmap)(pPriv->sourceBits);

    xfree (pPriv);

    return 0;
  }

  pGC = GetScratchGC(1, pScreen);

  if (pGC == NULL)
  {
    return 0;
  }

  gcvals[0] = GXcopyInverted;
  ChangeGC (pGC, GCFunction, gcvals);
  ValidateGC ((DrawablePtr)pPriv->sourceBits, pGC);
  (*pGC->ops->PutImage) ((DrawablePtr)pPriv->sourceBits, pGC, 1,
                          0, 0, pCursor->bits->width, pCursor->bits->height,
                          0, XYPixmap, (char *)pCursor->bits->source);

  gcvals[0] = GXand;
  ChangeGC (pGC, GCFunction, gcvals);
  ValidateGC ((DrawablePtr)pPriv->sourceBits, pGC);
  (*pGC->ops->PutImage) ((DrawablePtr)pPriv->sourceBits, pGC, 1,
                          0, 0, pCursor->bits->width, pCursor->bits->height,
                          0, XYPixmap, (char *)pCursor->bits->mask);

  gcvals[0] = GXcopyInverted;
  ChangeGC (pGC, GCFunction, gcvals);
  ValidateGC ((DrawablePtr)pPriv->maskBits, pGC);
  (*pGC->ops->PutImage) ((DrawablePtr)pPriv->maskBits, pGC, 1,
                          0, 0, pCursor->bits->width, pCursor->bits->height,
                          0, XYPixmap, (char *)pCursor->bits->mask);


  n = BitmapBytePad(nxwinCursorWidth) * nxwinCursorHeight;

  xorMask = xalloc(n);

  if (xorMask == NULL)
  {
    (*pScreen->DestroyPixmap)(pPriv->sourceBits);
    (*pScreen->DestroyPixmap)(pPriv->maskBits);

    xfree (pPriv);
    return 0;
  }

  andMask = xalloc(n);

  if (andMask == NULL)
  {
    (*pScreen->DestroyPixmap)(pPriv->sourceBits);
    (*pScreen->DestroyPixmap)(pPriv->maskBits);

    xfree(xorMask);
    xfree(pPriv);
    return 0;

  }

  pTempAnd = (*pScreen->CreatePixmap)(pScreen, nxwinCursorWidth,
                                nxwinCursorHeight, 1);

  if (pTempAnd == NULL)
  {
    (*pScreen->DestroyPixmap)(pPriv->sourceBits);
    (*pScreen->DestroyPixmap)(pPriv->maskBits);

    xfree(xorMask);
    xfree(andMask);
    xfree(pPriv);

    return 0;
  }

  pTempXor = (*pScreen->CreatePixmap)(pScreen, nxwinCursorWidth,
                                nxwinCursorHeight, 1);

  if (pTempXor == NULL)
  {
    (*pScreen->DestroyPixmap)(pPriv->sourceBits);
    (*pScreen->DestroyPixmap)(pPriv->maskBits);

    (*pScreen->DestroyPixmap)(pTempAnd);

    xfree(xorMask);
    xfree(andMask);
    xfree(pPriv);

    return 0;
  }

  backrect.x = backrect.y = 0;
  backrect.width = nxwinCursorWidth;
  backrect.height = nxwinCursorHeight;

  gcvals[0] = GXclear;
  ChangeGC(pGC, GCFunction, gcvals);
  ValidateGC((DrawablePtr)pTempXor, pGC);
  (*pGC->ops->PolyFillRect)((DrawablePtr)pTempXor, pGC, 1, &backrect);

  gcvals[0] = GXcopy;
  ChangeGC(pGC, GCFunction, gcvals);
  ValidateGC((DrawablePtr)pTempXor, pGC);
  (*pGC->ops->CopyArea)((DrawablePtr)pPriv->sourceBits,
                          (DrawablePtr)pTempXor, pGC, 0, 0,
				pCursor->bits->width,
                                pCursor->bits->height, 
			        0, 0);

  gcvals[0] = GXset;
  ChangeGC(pGC, GCFunction, gcvals);
  ValidateGC((DrawablePtr)pTempAnd, pGC);
  (*pGC->ops->PolyFillRect)((DrawablePtr)pTempAnd, pGC, 1, &backrect);

  gcvals[0] = GXcopy;
  ChangeGC(pGC, GCFunction, gcvals);
  ValidateGC((DrawablePtr)pTempAnd, pGC);
  (*pGC->ops->CopyArea)((DrawablePtr)pPriv->maskBits,
                          (DrawablePtr)pTempAnd, pGC, 0, 0,
				pCursor->bits->width,
                                pCursor->bits->height, 
			        0, 0);

  (*pScreen->GetImage)((DrawablePtr)pTempXor,
	                                         0,
				                 0,
				                 nxwinCursorWidth,
                                                 nxwinCursorHeight,
				                 XYPixmap,
				                 0xffffff,
				                 (pointer)xorMask);

  (*pScreen->GetImage)((DrawablePtr)pTempAnd,
	                                         0,
				                 0,
				                 nxwinCursorWidth,
                                                 nxwinCursorHeight,
				                 XYPixmap,
				                 0xffffff,
				                 (pointer)andMask);
  FreeScratchGC (pGC);

  for (i = 0; i < n; i++)
  {
    *(andMask + i) = nxwinFlipChar[*(andMask + i)]; 
  }

  for (i = 0; i < n; i++)
  {
    *(xorMask + i) = nxwinFlipChar[*(xorMask + i)]; 
  }

  nxwinCursorPriv(pCursor, pScreen)->cursor =
      CreateCursor(g_hInstance,
                   pCursor->bits->xhot,
                   pCursor->bits->yhot,
                   nxwinCursorWidth,
                   nxwinCursorHeight,
                   andMask,
                   xorMask);

  if (nxwinCursorPriv(pCursor, pScreen)->cursor == NULL)
  {
    ErrorF("nxwinRealizeCursor: Failed to create monochrome cursor.\n");
               
  }
  #ifdef DEBUG
  else
  {
    ErrorF("nxwinRealizeCursor: Created monochrome cursor with handle [%p].\n",
               nxwinCursorPriv(pCursor, pScreen)->cursor);
  }
  #endif

  xfree(andMask);
  xfree(xorMask);

  (*pScreen->DestroyPixmap) (pTempAnd);
  (*pScreen->DestroyPixmap) (pTempXor);

  return 1;
}

static int nxwinUnrealizeCursor(ScreenPtr pScreen, CursorPtr pCursor)
{
  nxwinPrivCursor *pPriv;

  pPriv = nxwinCursorPriv(pCursor, pScreen);

  if (pPriv && (pCursor->bits->refcnt <= 1))
  {
    if (pPriv->sourceBits)
      (*pScreen->DestroyPixmap) (pPriv->sourceBits);
    if (pPriv->maskBits)
      (*pScreen->DestroyPixmap) (pPriv->maskBits);
#ifdef ARGB_CURSOR

    if (pCursor->bits->argb != NULL && pPriv->argb != NULL)
    {
      #ifdef DEBUG
      ErrorF("nxwinUnrealizeCursor: Destroying ARGB cursor with handle [%p].\n",
                 nxwinCursorPriv(pCursor, pScreen)->cursor);
      #endif

      DestroyIcon(nxwinCursorPriv(pCursor, pScreen)->cursor);
    }
    else
#endif
    {
      #ifdef DEBUG
      ErrorF("nxwinUnrealizeCursor: Destroying monochrome cursor with handle "
                 "[%p].\n", nxwinCursorPriv(pCursor, pScreen)->cursor);
      #endif

      DestroyCursor(nxwinCursorPriv(pCursor, pScreen)->cursor);
    }

    xfree ((pointer) pPriv);

    pCursor->devPriv[pScreen->myNum] = (pointer)NULL;
  }
 
  return 1;
}

static void nxwinSetCursor(ScreenPtr pScreen, CursorPtr pCursor, int x, int y)
{
  if (pCursor == rootCursor)
  {
    #ifdef DEBUG
    ErrorF("nxwinSetCursor: Setting root cursor as an arrow.\n");
    #endif

    nxwinCurrentCursor = LoadCursor(NULL, IDC_ARROW);

    SetCursor(nxwinCurrentCursor);
  }
  else if (pCursor != NULL)
  {
    #ifdef DEBUG
    ErrorF("nxwinSetCursor: Setting cursor with handle [%p].\n",
               nxwinCursorPriv(pCursor, pScreen) -> cursor);
    #endif

    nxwinCurrentCursor = nxwinCursorPriv(pCursor, pScreen) -> cursor;

    SetCursor(nxwinCurrentCursor);
  }

  return;
}

static void nxwinMoveCursor(ScreenPtr pScreen, int x, int y)
{
  return;
}

miPointerSpriteFuncRec nxwinPointerSpriteFuncs =
{
    nxwinRealizeCursor,
    nxwinUnrealizeCursor,
    nxwinSetCursor,
    nxwinMoveCursor,
};

#endif
