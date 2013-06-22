//	VirtualDub - Video processing and capture application
//	System library component
//	Copyright (C) 1998-2004 Avery Lee, All Rights Reserved.
//
//	Beginning with 1.6.0, the VirtualDub system library is licensed
//	differently than the remainder of VirtualDub.  This particular file is
//	thus licensed as follows (the "zlib" license):
//
//	This software is provided 'as-is', without any express or implied
//	warranty.  In no event will the authors be held liable for any
//	damages arising from the use of this software.
//
//	Permission is granted to anyone to use this software for any purpose,
//	including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//
//	1.	The origin of this software must not be misrepresented; you must
//		not claim that you wrote the original software. If you use this
//		software in a product, an acknowledgment in the product
//		documentation would be appreciated but is not required.
//	2.	Altered source versions must be plainly marked as such, and must
//		not be misrepresented as being the original software.
//	3.	This notice may not be removed or altered from any source
//		distribution.

#include <vd2/system/w32assist.h>
#include <vd2/system/text.h>
#include <vd2/system/vdstl.h>

int VDGetSizeOfBitmapHeaderW32(const BITMAPINFOHEADER *pHdr) {
	int palents = 0;

	if (pHdr->biCompression == BI_RGB && pHdr->biBitCount <= 8) {
		palents = pHdr->biClrUsed;
		if (!palents)
			palents = 1 << pHdr->biBitCount;
	}
	int size = pHdr->biSize + palents * sizeof(RGBQUAD);

	if (pHdr->biSize < sizeof(BITMAPV4HEADER) && pHdr->biCompression == BI_BITFIELDS)
		size += sizeof(DWORD) * 3;

	return size;
}

void VDSetWindowTextW32(HWND hwnd, const wchar_t *s) {
	if (VDIsWindowsNT()) {
		SetWindowTextW(hwnd, s);
	} else {
		SetWindowTextA(hwnd, VDTextWToA(s).c_str());
	}
}

VDStringW VDGetWindowTextW32(HWND hwnd) {
	union {
		wchar_t w[256];
		char a[512];
	} buf;

	if (VDIsWindowsNT()) {
		int len = GetWindowTextLengthW(hwnd);

		if (len > 255) {
			vdblock<wchar_t> tmp(len + 1);
			len = GetWindowTextW(hwnd, tmp.data(), tmp.size());

			VDStringW text(tmp.data(), len);
			return text;
		} else if (len > 0) {
			len = GetWindowTextW(hwnd, buf.w, 256);

			VDStringW text(buf.w, len);
			return text;
		}
	} else {
		int len = GetWindowTextLengthA(hwnd);

		if (len > 511) {
			vdblock<char> tmp(len + 1);
			len = GetWindowTextA(hwnd, tmp.data(), tmp.size());

			VDStringW text(VDTextAToW(tmp.data(), len));
			return text;
		} else if (len > 0) {
			len = GetWindowTextA(hwnd, buf.a, 512);

			VDStringW text(VDTextAToW(buf.a, len));
			return text;
		}
	}

	return VDStringW();
}

void VDAppendMenuW32(HMENU hmenu, UINT flags, UINT id, const wchar_t *text){
	if (VDIsWindowsNT()) {
		AppendMenuW(hmenu, flags, id, text);
	} else {
		AppendMenuA(hmenu, flags, id, VDTextWToA(text).c_str());
	}
}

void VDCheckMenuItemByCommandW32(HMENU hmenu, UINT cmd, bool checked) {
	CheckMenuItem(hmenu, cmd, checked ? MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED);
}

void VDEnableMenuItemByCommandW32(HMENU hmenu, UINT cmd, bool checked) {
	EnableMenuItem(hmenu, cmd, checked ? MF_BYCOMMAND|MF_ENABLED : MF_BYCOMMAND|MF_GRAYED);
}

void VDSetMenuItemTextByCommandW32(HMENU hmenu, UINT cmd, const wchar_t *text) {
	if (VDIsWindowsNT()) {
		MENUITEMINFOW mmiW;

		mmiW.cbSize		= MENUITEMINFO_SIZE_VERSION_400W;
		mmiW.fMask		= MIIM_TYPE;
		mmiW.fType		= MFT_STRING;
		mmiW.dwTypeData	= (LPWSTR)text;

		SetMenuItemInfoW(hmenu, cmd, FALSE, &mmiW);
	} else {
		MENUITEMINFOA mmiA;
		VDStringA textA(VDTextWToA(text));

		mmiA.cbSize		= MENUITEMINFO_SIZE_VERSION_400A;
		mmiA.fMask		= MIIM_TYPE;
		mmiA.fType		= MFT_STRING;
		mmiA.dwTypeData	= (LPSTR)textA.c_str();

		SetMenuItemInfoA(hmenu, cmd, FALSE, &mmiA);
	}
}

LRESULT	VDDualCallWindowProcW32(WNDPROC wp, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return (IsWindowUnicode(hwnd) ? CallWindowProcW : CallWindowProcA)(wp, hwnd, msg, wParam, lParam);
}

LRESULT VDDualDefWindowProcW32(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return IsWindowUnicode(hwnd) ? DefWindowProcW(hwnd, msg, wParam, lParam) : DefWindowProcA(hwnd, msg, wParam, lParam);
}

EXECUTION_STATE VDSetThreadExecutionStateW32(EXECUTION_STATE esFlags) {
	EXECUTION_STATE es = 0;

	// SetThreadExecutionState(): requires Windows 98+/2000+.
	typedef EXECUTION_STATE (WINAPI *tSetThreadExecutionState)(EXECUTION_STATE);
	static tSetThreadExecutionState pFunc = (tSetThreadExecutionState)GetProcAddress(GetModuleHandle("kernel32"), "SetThreadExecutionState");

	if (pFunc)
		es = pFunc(esFlags);

	return es;
}

bool VDSetFilePointerW32(HANDLE h, sint64 pos, DWORD dwMoveMethod) {
	LONG posHi = (LONG)(pos >> 32);
	DWORD result = SetFilePointer(h, (LONG)pos, &posHi, dwMoveMethod);

	if (result != INVALID_SET_FILE_POINTER)
		return true;

	DWORD dwError = GetLastError();

	return (dwError == NO_ERROR);
}

bool VDGetFileSizeW32(HANDLE h, sint64& size) {
	DWORD dwSizeHigh;
	DWORD dwSizeLow = GetFileSize(h, &dwSizeHigh);

	if (dwSizeLow == (DWORD)-1 && GetLastError() != NO_ERROR)
		return false;

	size = dwSizeLow + ((sint64)dwSizeHigh << 32);
	return true;
}

bool VDDrawTextW32(HDC hdc, const wchar_t *s, int nCount, LPRECT lpRect, UINT uFormat) {
	RECT r;
	if (VDIsWindowsNT()) {
		// If multiline and vcentered (not normally supported...)
		if (!((uFormat ^ DT_VCENTER) & (DT_VCENTER|DT_SINGLELINE))) {
			uFormat &= ~DT_VCENTER;

			r = *lpRect;
			if (!DrawTextW(hdc, s, nCount, &r, uFormat | DT_CALCRECT))
				return false;

			int dx = ((lpRect->right - lpRect->left) - (r.right - r.left)) >> 1;
			int dy = ((lpRect->bottom - lpRect->top) - (r.bottom - r.top)) >> 1;

			r.left += dx;
			r.right += dx;
			r.top += dy;
			r.bottom += dy;
			lpRect = &r;
		}

		return !!DrawTextW(hdc, s, nCount, lpRect, uFormat);
	} else {
		VDStringA strA(VDTextWToA(s, nCount));

		// If multiline and vcentered (not normally supported...)
		if (!((uFormat ^ DT_VCENTER) & (DT_VCENTER|DT_SINGLELINE))) {
			uFormat &= ~DT_VCENTER;

			r = *lpRect;
			if (!DrawTextA(hdc, strA.data(), strA.size(), &r, uFormat | DT_CALCRECT))
				return false;

			int dx = ((lpRect->right - lpRect->left) - (r.right - r.left)) >> 1;
			int dy = ((lpRect->bottom - lpRect->top) - (r.bottom - r.top)) >> 1;

			r.left += dx;
			r.right += dx;
			r.top += dy;
			r.bottom += dy;
			lpRect = &r;
		}

		return !!DrawTextA(hdc, strA.data(), strA.size(), lpRect, uFormat);
	}
}

bool VDPatchModuleImportTableW32(HMODULE hmod, const char *srcModule, const char *name, void *pCompareValue, void *pNewValue, void *volatile *ppOldValue) {
	char *pBase = (char *)hmod;

	__try {
		// The PEheader offset is at hmod+0x3c.  Add the size of the optional header
		// to step to the section headers.

		const uint32 peoffset = ((const long *)pBase)[15];
		const uint32 signature = *(uint32 *)(pBase + peoffset);

		if (signature != IMAGE_NT_SIGNATURE)
			return false;

		const IMAGE_FILE_HEADER *pHeader = (const IMAGE_FILE_HEADER *)(pBase + peoffset + 4);

		// Verify the PE optional structure.

		if (pHeader->SizeOfOptionalHeader < 104)
			return false;

		// Find import header.

		const IMAGE_IMPORT_DESCRIPTOR *pImportDir;
		int nImports;

		switch(*(short *)((char *)pHeader + IMAGE_SIZEOF_FILE_HEADER)) {

#ifdef _M_AMD64
		case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
			{
				const IMAGE_OPTIONAL_HEADER64 *pOpt = (IMAGE_OPTIONAL_HEADER64 *)((const char *)pHeader + sizeof(IMAGE_FILE_HEADER));

				if (pOpt->NumberOfRvaAndSizes < 2)
					return false;

				pImportDir = (const IMAGE_IMPORT_DESCRIPTOR *)(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
				nImports = pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size / sizeof(IMAGE_IMPORT_DESCRIPTOR);
			}
			break;
#else
		case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
			{
				const IMAGE_OPTIONAL_HEADER32 *pOpt = (IMAGE_OPTIONAL_HEADER32 *)((const char *)pHeader + sizeof(IMAGE_FILE_HEADER));

				if (pOpt->NumberOfRvaAndSizes < 2)
					return false;

				pImportDir = (const IMAGE_IMPORT_DESCRIPTOR *)(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
				nImports = pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size / sizeof(IMAGE_IMPORT_DESCRIPTOR);
			}
			break;
#endif

		default:		// reject PE32+
			return false;
		}

		// Hmmm... no imports?

		if ((const char *)pImportDir == pBase)
			return false;

		// Scan down the import entries.  We are looking for MSVFW32.

		int i;

		for(i=0; i<nImports; ++i) {
			if (!stricmp(pBase + pImportDir[i].Name, srcModule))
				return false;
		}

		if (i >= nImports)
			return false;

		// Found it.  Start scanning MSVFW32 imports until we find DrawDibDraw.

		const long *pImports = (const long *)(pBase + pImportDir[i].OriginalFirstThunk);
		void * volatile *pVector = (void * volatile *)(pBase + pImportDir[i].FirstThunk);

		while(*pImports) {
			if (*pImports >= 0) {
				const char *pName = pBase + *pImports + 2;

				if (!strcmp(pName, name)) {

					// Found it!  Reset the protection.

					DWORD dwOldProtect;

					if (VirtualProtect((void *)pVector, sizeof(void *), PAGE_EXECUTE_READWRITE, &dwOldProtect)) {
						if (ppOldValue) {
							for(;;) {
								void *old = *pVector;
								if (pCompareValue && pCompareValue != old)
									return false;

								*ppOldValue = old;
								if (old == VDAtomicCompareExchangePointer(pVector, pNewValue, old))
									break;
							}
						} else {
							*pVector = pNewValue;
						}

						VirtualProtect((void *)pVector, sizeof(void *), dwOldProtect, &dwOldProtect);

						return true;
					}

					break;
				}
			}

			++pImports;
			++pVector;
		}
	} __except(1) {
	}

	return false;
}