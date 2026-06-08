#include "dxshell.h"
#include <intrin.h>
#include "../../inject.h"
#include "function_stubs.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "cmdline.h"

namespace tomb4
{
	DXPTR* &G_dxptr = *reinterpret_cast<decltype(&G_dxptr)>(0x754468);
	char (&keymap)[256] = *reinterpret_cast<decltype(&keymap)>(0x754260);
	DXINFO* &G_dxinfo = *reinterpret_cast<decltype(&G_dxinfo)>(0x754088);
	HWND &G_hwnd = *reinterpret_cast<decltype(&G_hwnd)>(0x754080);

	long DXAttempt(HRESULT r)
	{
		const char* string;

		// sostituisce funzione GestioneErroreDX()
		// per salvare ultimo errore directx
		// in ecx c'e' il codice dell'errore

		// dovrebbe essere l'indirizzo di ritorno
		trng::LastReturnDX = (DWORD)_ReturnAddress();

		if (SUCCEEDED(r))
			return DD_OK;

		string = DXGetErrorString(r);

		trng::AnalisiErroreDirectX(string, trng::LastReturnDX);

		Log(1, "ERROR : %s", string);
		return DD_FALSE;
	}

	void DXReadKeyboard(char* KeyMap)
	{
		__try { throw __func__; } __finally {}
	}

	const char* DXGetErrorString(HRESULT hr)
	{
		switch (hr)
		{
		case DD_OK:
			return "The request completed successfully.";

		case DDERR_ALREADYINITIALIZED:
			return "The object has already been initialized.";

		case DDERR_BLTFASTCANTCLIP:
			return "A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface4::BltFast method.";

		case DDERR_CANNOTATTACHSURFACE:
			return "A surface cannot be attached to another requested surface.";

		case DDERR_CANNOTDETACHSURFACE:
			return "A surface cannot be detached from another requested surface.";

		case DDERR_CANTCREATEDC:
			return "Windows can not create any more device contexts (DCs), or a DC was requested for a palette-indexed surface when the surface had no palette and the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC).";

		case DDERR_CANTDUPLICATE:
			return "Primary and 3-D surfaces, or surfaces that are implicitly created, cannot be duplicated. ";

		case DDERR_CANTLOCKSURFACE:
			return "Access to this surface is refused because an attempt was made to lock the primary surface without DCI support. ";

		case DDERR_CANTPAGELOCK:
			return "An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface. ";

		case DDERR_CANTPAGEUNLOCK:
			return "An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface. ";

		case DDERR_CLIPPERISUSINGHWND:
			return "An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle. ";

		case DDERR_COLORKEYNOTSET:
			return "No source color key is specified for this operation. ";

		case DDERR_CURRENTLYNOTAVAIL:
			return "No support is currently available. ";

		case DDERR_DCALREADYCREATED:
			return "A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface. ";

		case DDERR_DEVICEDOESNTOWNSURFACE:
			return "Surfaces created by one DirectDraw device cannot be used directly by another DirectDraw device. ";

		case DDERR_DIRECTDRAWALREADYCREATED:
			return "A DirectDraw object representing this driver has already been created for this process. ";

		case DDERR_EXCEPTION:
			return "An exception was encountered while performing the requested operation. ";

		case DDERR_EXCLUSIVEMODEALREADYSET:
			return "An attempt was made to set the cooperative level when it was already set to exclusive. ";

		case DDERR_EXPIRED:
			return "The data has expired and is therefore no longer valid. ";

		case DDERR_GENERIC:
			return "There is an undefined error condition. ";

		case DDERR_HEIGHTALIGN:
			return "The height of the provided rectangle is not a multiple of the required alignment. ";

		case DDERR_HWNDALREADYSET:
			return "The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created. ";

		case DDERR_HWNDSUBCLASSED:
			return "DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed. ";

		case DDERR_IMPLICITLYCREATED:
			return "The surface cannot be restored because it is an implicitly created surface. ";

		case DDERR_INCOMPATIBLEPRIMARY:
			return "The primary surface creation request does not match with the existing primary surface. ";

		case DDERR_INVALIDCAPS:
			return "One or more of the capability bits passed to the callback function are incorrect. ";

		case DDERR_INVALIDCLIPLIST:
			return "DirectDraw does not support the provided clip list. ";

		case DDERR_INVALIDDIRECTDRAWGUID:
			return "The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier. ";

		case DDERR_INVALIDMODE:
			return "DirectDraw does not support the requested mode. ";

		case DDERR_INVALIDOBJECT:
			return "DirectDraw received a pointer that was an invalid DirectDraw object. ";

		case DDERR_INVALIDPARAMS:
			return "One or more of the parameters passed to the method are incorrect. ";

		case DDERR_INVALIDPIXELFORMAT:
			return "The pixel format was invalid as specified. ";

		case DDERR_INVALIDPOSITION:
			return "The position of the overlay on the destination is no longer legal. ";

		case DDERR_INVALIDRECT:
			return "The provided rectangle was invalid. ";

		case DDERR_INVALIDSTREAM:
			return "The specified stream contains invalid data. ";

		case DDERR_INVALIDSURFACETYPE:
			return "The requested operation could not be performed because the surface was of the wrong type. ";

		case DDERR_LOCKEDSURFACES:
			return "One or more surfaces are locked, causing the failure of the requested operation. ";

		case DDERR_MOREDATA:
			return "There is more data available than the specified buffer size can hold. ";

		case DDERR_NO3D:
			return "No 3-D hardware or emulation is present. ";

		case DDERR_NOALPHAHW:
			return "No alpha acceleration hardware is present or available, causing the failure of the requested operation. ";

		case DDERR_NOBLTHW:
			return "No blitter hardware is present. ";

		case DDERR_NOCLIPLIST:
			return "No clip list is available. ";

		case DDERR_NOCLIPPERATTACHED:
			return "No DirectDrawClipper object is attached to the surface object. ";

		case DDERR_NOCOLORCONVHW:
			return "The operation cannot be carried out because no color-conversion hardware is present or available. ";

		case DDERR_NOCOLORKEY:
			return "The surface does not currently have a color key. ";

		case DDERR_NOCOLORKEYHW:
			return "The operation cannot be carried out because there is no hardware support for the destination color key. ";

		case DDERR_NOCOOPERATIVELEVELSET:
			return "A create function is called without the IDirectDraw4::SetCooperativeLevel method being called. ";

		case DDERR_NODC:
			return "No DC has ever been created for this surface. ";

		case DDERR_NODDROPSHW:
			return "No DirectDraw raster operation (ROP) hardware is available. ";

		case DDERR_NODIRECTDRAWHW:
			return "Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware. ";

		case DDERR_NODIRECTDRAWSUPPORT:
			return "DirectDraw support is not possible with the current display driver. ";

		case DDERR_NOEMULATION:
			return "Software emulation is not available. ";

		case DDERR_NOEXCLUSIVEMODE:
			return "The operation requires the application to have exclusive mode, but the application does not have exclusive mode. ";

		case DDERR_NOFLIPHW:
			return "Flipping visible surfaces is not supported. ";

		case DDERR_NOFOCUSWINDOW:
			return "An attempt was made to create or set a device window without first setting the focus window. ";

		case DDERR_NOGDI:
			return "No GDI is present. ";

		case DDERR_NOHWND:
			return "Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle. ";

		case DDERR_NOMIPMAPHW:
			return "The operation cannot be carried out because no mipmap capable texture mapping hardware is present or available. ";

		case DDERR_NOMIRRORHW:
			return "The operation cannot be carried out because no mirroring hardware is present or available. ";

		case DDERR_NONONLOCALVIDMEM:
			return "An attempt was made to allocate non-local video memory from a device that does not support non-local video memory. ";

		case DDERR_NOOPTIMIZEHW:
			return "The device does not support optimized surfaces. ";

		case DDERR_NOOVERLAYDEST:
			return "The IDirectDrawSurface4::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface4::UpdateOverlay method has not been called on to establish a destination. ";

		case DDERR_NOOVERLAYHW:
			return "The operation cannot be carried out because no overlay hardware is present or available. ";

		case DDERR_NOPALETTEATTACHED:
			return "No palette object is attached to this surface. ";

		case DDERR_NOPALETTEHW:
			return "There is no hardware support for 16- or 256-color palettes. ";

		case DDERR_NORASTEROPHW:
			return "The operation cannot be carried out because no appropriate raster operation hardware is present or available. ";

		case DDERR_NOROTATIONHW:
			return "The operation cannot be carried out because no rotation hardware is present or available. ";

		case DDERR_NOSTRETCHHW:
			return "The operation cannot be carried out because there is no hardware support for stretching. ";

		case DDERR_NOT4BITCOLOR:
			return "The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette. ";

		case DDERR_NOT4BITCOLORINDEX:
			return "The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette. ";

		case DDERR_NOT8BITCOLOR:
			return "The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette. ";

		case DDERR_NOTAOVERLAYSURFACE:
			return "An overlay component is called for a non-overlay surface. ";

		case DDERR_NOTEXTUREHW:
			return "The operation cannot be carried out because no texture-mapping hardware is present or available. ";

		case DDERR_NOTFLIPPABLE:
			return "An attempt has been made to flip a surface that cannot be flipped. ";

		case DDERR_NOTFOUND:
			return "The requested item was not found. ";

		case DDERR_NOTINITIALIZED:
			return "An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized. ";

		case DDERR_NOTLOADED:
			return "The surface is an optimized surface, but it has not yet been allocated any memory. ";

		case DDERR_NOTLOCKED:
			return "An attempt is made to unlock a surface that was not locked. ";

		case DDERR_NOTPAGELOCKED:
			return "An attempt is made to page unlock a surface with no outstanding page locks. ";

		case DDERR_NOTPALETTIZED:
			return "The surface being used is not a palette-based surface. ";

		case DDERR_NOVSYNCHW:
			return "The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations. ";

		case DDERR_NOZBUFFERHW:
			return "The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers. ";

		case DDERR_NOZOVERLAYHW:
			return "The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays. ";

		case DDERR_OUTOFCAPS:
			return "The hardware needed for the requested operation has already been allocated. ";

		case DDERR_OUTOFMEMORY:
			return "DirectDraw does not have enough memory to perform the operation. ";

		case DDERR_OUTOFVIDEOMEMORY:
			return "DirectDraw does not have enough display memory to perform the operation. ";

		case DDERR_OVERLAPPINGRECTS:
			return "Operation could not be carried out because the source and destination rectangles are on the same surface and overlap each other. ";

		case DDERR_OVERLAYCANTCLIP:
			return "The hardware does not support clipped overlays. ";

		case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
			return "An attempt was made to have more than one color key active on an overlay. ";

		case DDERR_OVERLAYNOTVISIBLE:
			return "The IDirectDrawSurface4::GetOverlayPosition method is called on a hidden overlay. ";

		case DDERR_PALETTEBUSY:
			return "Access to this palette is refused because the palette is locked by another thread. ";

		case DDERR_PRIMARYSURFACEALREADYEXISTS:
			return "This process has already created a primary surface. ";

		case DDERR_REGIONTOOSMALL:
			return "The region passed to the IDirectDrawClipper::GetClipList method is too small. ";

		case DDERR_SURFACEALREADYATTACHED:
			return "An attempt was made to attach a surface to another surface to which it is already attached. ";

		case DDERR_SURFACEALREADYDEPENDENT:
			return "An attempt was made to make a surface a dependency of another surface to which it is already dependent. ";

		case DDERR_SURFACEBUSY:
			return "Access to the surface is refused because the surface is locked by another thread. ";

		case DDERR_SURFACEISOBSCURED:
			return "Access to the surface is refused because the surface is obscured. ";

		case DDERR_SURFACELOST:
			return "Access to the surface is refused because the surface memory is gone. Call the IDirectDrawSurface4::Restore method on this surface to restore the memory associated with it. ";

		case DDERR_SURFACENOTATTACHED:
			return "The requested surface is not attached. ";

		case DDERR_TOOBIGHEIGHT:
			return "The height requested by DirectDraw is too large. ";

		case DDERR_TOOBIGSIZE:
			return "The size requested by DirectDraw is too large. However, the individual height and width are valid sizes. ";

		case DDERR_TOOBIGWIDTH:
			return "The width requested by DirectDraw is too large. ";

		case DDERR_UNSUPPORTED:
			return "The operation is not supported. ";

		case DDERR_UNSUPPORTEDFORMAT:
			return "The FourCC format requested is not supported by DirectDraw. ";

		case DDERR_UNSUPPORTEDMASK:
			return "The bitmask in the pixel format requested is not supported by DirectDraw. ";

		case DDERR_UNSUPPORTEDMODE:
			return "The display is currently in an unsupported mode. ";

		case DDERR_VERTICALBLANKINPROGRESS:
			return "A vertical blank is in progress. ";

		case DDERR_VIDEONOTACTIVE:
			return "The video port is not active. ";

		case DDERR_WASSTILLDRAWING:
			return "The previous blit operation that is transferring information to or from this surface is incomplete. ";

		case DDERR_WRONGMODE:
			return "This surface cannot be restored because it was created in a different mode. ";

		case DDERR_XALIGN:
			return "The provided rectangle was not horizontally aligned on a required boundary. ";

		case D3DERR_BADMAJORVERSION:
			return "Bad major version";

		case D3DERR_BADMINORVERSION:
			return "Bad minor version";

		case D3DERR_COLORKEYATTACHED:
			return "Colorkey attached";

		case D3DERR_CONFLICTINGTEXTUREFILTER:
			return "Conflicting texture filter";

		case D3DERR_CONFLICTINGTEXTUREPALETTE:
			return "Conflicting texture palette";

		case D3DERR_CONFLICTINGRENDERSTATE:
			return "Conflicting render state";

		case D3DERR_DEVICEAGGREGATED:
			return "Device aggregated";

		case D3DERR_EXECUTE_CLIPPED_FAILED:
			return "Execute clipped failed";

		case D3DERR_EXECUTE_CREATE_FAILED:
			return "Execute create failed";

		case D3DERR_EXECUTE_DESTROY_FAILED:
			return "Execute destroy failed";

		case D3DERR_EXECUTE_FAILED:
			return "Execute failed";

		case D3DERR_EXECUTE_LOCK_FAILED:
			return "Execute lock failed";

		case D3DERR_EXECUTE_LOCKED:
			return "Execute locked";

		case D3DERR_EXECUTE_NOT_LOCKED:
			return "Execute not locked";

		case D3DERR_EXECUTE_UNLOCK_FAILED:
			return "Execute unlock failed";

		case D3DERR_INITFAILED:
			return "Init failed";

		case D3DERR_INBEGIN:
			return "Already in begin scene";

		case D3DERR_INVALID_DEVICE:
			return "Invalid device";

		case D3DERR_INVALIDCURRENTVIEWPORT:
			return "Invalid current viewport";

		case D3DERR_INVALIDMATRIX:
			return "Invalid matrix";

		case D3DERR_INVALIDPALETTE:
			return "Invalid palette";

		case D3DERR_INVALIDPRIMITIVETYPE:
			return "Invalid primitive type";

		case D3DERR_INVALIDRAMPTEXTURE:
			return "Invalid ramp texture";

		case D3DERR_INVALIDVERTEXFORMAT:
			return "Invalid vertex format";

		case D3DERR_INVALIDVERTEXTYPE:
			return "Invalid vertex type";

		case D3DERR_LIGHT_SET_FAILED:
			return "Light set failed";

		case D3DERR_LIGHTHASVIEWPORT:
			return "Light has viewport";

		case D3DERR_LIGHTNOTINTHISVIEWPORT:
			return "Light not in this viewport";

		case D3DERR_MATERIAL_CREATE_FAILED:
			return "Material create failed";

		case D3DERR_MATERIAL_DESTROY_FAILED:
			return "Material destroy failed";

		case D3DERR_MATERIAL_GETDATA_FAILED:
			return "Material get data failed";

		case D3DERR_MATERIAL_SETDATA_FAILED:
			return "Material set data failed";

		case D3DERR_MATRIX_CREATE_FAILED:
			return "Matrix create failed";

		case D3DERR_MATRIX_DESTROY_FAILED:
			return "Matrix destroy failed";

		case D3DERR_MATRIX_GETDATA_FAILED:
			return "Matrix get data failed";

		case D3DERR_MATRIX_SETDATA_FAILED:
			return "Matrix set data failed";

		case D3DERR_NOCURRENTVIEWPORT:
			return "No current viewport";

		case D3DERR_NOTINBEGIN:
			return "Not in begin scene";

		case D3DERR_NOVIEWPORTS:
			return "No viewports";

		case D3DERR_SCENE_BEGIN_FAILED:
			return "Begin scene failed";

		case D3DERR_SCENE_END_FAILED:
			return "End scene failed";

		case D3DERR_SCENE_IN_SCENE:
			return "Scene in scene";

		case D3DERR_SCENE_NOT_IN_SCENE:
			return "Scene not in scene";

		case D3DERR_SETVIEWPORTDATA_FAILED:
			return "Set viewport data failed";

		case D3DERR_STENCILBUFFER_NOTPRESENT:
			return "Stencil buffer not present";

		case D3DERR_SURFACENOTINVIDMEM:
			return "Surface not in video memory";

		case D3DERR_TEXTURE_BADSIZE:
			return "Bad texture size";

		case D3DERR_TEXTURE_CREATE_FAILED:
			return "Texture create failed";

		case D3DERR_TEXTURE_DESTROY_FAILED:
			return "Texture destroy failed";

		case D3DERR_TEXTURE_GETSURF_FAILED:
			return "Texture get surface failed";

		case D3DERR_TEXTURE_LOAD_FAILED:
			return "Texture load failed";

		case D3DERR_TEXTURE_LOCK_FAILED:
			return "Texture lock failed";

		case D3DERR_TEXTURE_LOCKED:
			return "Texture lock failed";

		case D3DERR_TEXTURE_NO_SUPPORT:
			return "Texture no support";

		case D3DERR_TEXTURE_NOT_LOCKED:
			return "Texture not locked";

		case D3DERR_TEXTURE_SWAP_FAILED:
			return "Texture swap failed";

		case D3DERR_TEXTURE_UNLOCK_FAILED:
			return "Texture unlock failed";

		case D3DERR_TOOMANYOPERATIONS:
			return "Too many operations";

		case D3DERR_TOOMANYPRIMITIVES:
			return "Too many primitives";

		case D3DERR_UNSUPPORTEDALPHAARG:
			return "Unsupported alpha argument";

		case D3DERR_UNSUPPORTEDALPHAOPERATION:
			return "Unsupported alpha operation";

		case D3DERR_UNSUPPORTEDCOLORARG:
			return "Unsupported color argument";

		case D3DERR_UNSUPPORTEDCOLOROPERATION:
			return "Unsupported color opertation";

		case D3DERR_UNSUPPORTEDFACTORVALUE:
			return "Unsupported factor value";

		case D3DERR_UNSUPPORTEDTEXTUREFILTER:
			return "Unsupported texture filter";

		case D3DERR_VBUF_CREATE_FAILED:
			return "Vertex buffer create failed";

		case D3DERR_VERTEXBUFFERLOCKED:
			return "Vertex buffer locked";

		case D3DERR_VERTEXBUFFEROPTIMIZED:
			return "Vertex buffer optimised";

		case D3DERR_VIEWPORTDATANOTSET:
			return "Viewport data not set";

		case D3DERR_VIEWPORTHASNODEVICE:
			return "Viewport has no device";

		case D3DERR_WRONGTEXTUREFORMAT:
			return "Wrong texture format";

		case D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY:
			return "ZBuffer needs system memory";

		case D3DERR_ZBUFF_NEEDS_VIDEOMEMORY:
			return "ZBuffer needs video memory";

		case D3DERR_ZBUFFER_NOTPRESENT:
			return "ZBuffer not present";

		case DSERR_ALLOCATED:
			return "The request failed because resources, such as a priority level, were already in use by another caller. ";

		case DSERR_ALREADYINITIALIZED:
			return "The object is already initialized. ";

		case DSERR_BADFORMAT:
			return "The specified wave format is not supported. ";

		case DSERR_BUFFERLOST:
			return "The buffer memory has been lost and must be restored. ";

		case DSERR_CONTROLUNAVAIL:
			return "The buffer control (volume, pan, and so on) requested by the caller is not available. ";

		case DSERR_INVALIDCALL:
			return "This function is not valid for the current state of this object. ";

		case DSERR_NOAGGREGATION:
			return "The object does not support aggregation. ";

		case DSERR_NODRIVER:
			return "No sound driver is available for use. ";

		case DSERR_NOINTERFACE:
			return "The requested COM interface is not available. ";

		case DSERR_OTHERAPPHASPRIO:
			return "Another application has a higher priority level, preventing this call from succeeding ";

		case DSERR_PRIOLEVELNEEDED:
			return "The caller does not have the priority level required for the function to succeed. ";

		case DSERR_UNINITIALIZED:
			return "The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called. ";
		}

		return "Undefined Error";
	}

	void DXFreeInfo(DXINFO* dxinfo)
	{
		__try { throw __func__; } __finally {}
	}

	void DXClose()
	{
		__try { throw __func__; } __finally {}
	}

	long DXGetInfo(DXINFO* dxinfo, HWND hwnd)
	{
		Log(2, "DXInitialise");
		G_hwnd = hwnd;
		Log(5, "Enumerating DirectDraw Devices");
		DXAttempt(DirectDrawEnumerate(DXEnumDirectDraw, dxinfo));
		DXAttempt(DirectSoundEnumerate(DXEnumDirectSound, dxinfo));

		if (trng::GlobTomb4.TestForceSetup)
			start_setup = true;

		G_dxinfo = dxinfo;
		return 1;
	}

	BOOL __stdcall DXEnumDirectDraw(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext)
	{
		__try { throw __func__; } __finally {}
	}

	BOOL __stdcall DXEnumDirectSound(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
	{
		__try { throw __func__; } __finally {}
	}

	HRESULT DXShowFrame()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Dxshell(bool replace)
{
	ProcessInject(0x48F8A0, (unsigned int)tomb4::DXAttempt, replace);
	ProcessInject(0x492090, (unsigned int)tomb4::DXReadKeyboard, false);
	ProcessInject(0x48EC60, (unsigned int)tomb4::DXGetErrorString, replace);
	ProcessInject(0x48F9D0, (unsigned int)tomb4::DXFreeInfo, false);
	ProcessInject(0x4917E0, (unsigned int)tomb4::DXClose, false);
	ProcessInject(0x48F8D0, (unsigned int)tomb4::DXGetInfo, replace);
	ProcessInject(0x48FC30, (unsigned int)tomb4::DXEnumDirectDraw, false);
	ProcessInject(0x48F930, (unsigned int)tomb4::DXEnumDirectSound, false);
	ProcessInject(0x491B40, (unsigned int)tomb4::DXShowFrame, false);
}
