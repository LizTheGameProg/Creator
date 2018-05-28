// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2013 NVIDIA Corporation. All rights reserved.



#ifndef __PVRT_H__
#define __PVRT_H__

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <assert.h>

#include <CoreFoundation/CFByteOrder.h>

#define PVR_TEXTURE_FLAG_TYPE_MASK	0xff

static const char* gPVRTexIdentifier = "PVR!";

enum
{
	kPVRTextureFlagTypePVRTC_2 = 24,
	kPVRTextureFlagTypePVRTC_4
};

struct PVRTexHeader
{
	uint32_t headerLength;
	uint32_t height;
	uint32_t width;
	uint32_t numMipmaps;
	uint32_t flags;
	uint32_t dataLength;
	uint32_t bpp;
	uint32_t bitmaskRed;
	uint32_t bitmaskGreen;
	uint32_t bitmaskBlue;
	uint32_t bitmaskAlpha;
	uint32_t pvrTag;
	uint32_t numSurfs;
};

struct PVRTextureInfo
{
	PVRTextureInfo(const char* buffer) : 
		data(NULL),
		width(0),
		height(0),
		glFormat(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG),
		hasAlpha(false)
	{
		const PVRTexHeader* header = reinterpret_cast<const PVRTexHeader*>(buffer);
		uint32_t pvrTag = CFSwapInt32LittleToHost(header->pvrTag);
		
		if (gPVRTexIdentifier[0] != ((pvrTag >>  0) & 0xff) ||
			gPVRTexIdentifier[1] != ((pvrTag >>  8) & 0xff) ||
			gPVRTexIdentifier[2] != ((pvrTag >> 16) & 0xff) ||
			gPVRTexIdentifier[3] != ((pvrTag >> 24) & 0xff))
		{
			return;
		}
		
		uint32_t flags = CFSwapInt32LittleToHost(header->flags);
		uint32_t formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;
		
		if (formatFlags == kPVRTextureFlagTypePVRTC_4 || formatFlags == kPVRTextureFlagTypePVRTC_2)
		{			
			if (formatFlags == kPVRTextureFlagTypePVRTC_4)
				glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
			else if (formatFlags == kPVRTextureFlagTypePVRTC_2)
				glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
			
			width = CFSwapInt32LittleToHost(header->width);
			height = CFSwapInt32LittleToHost(header->height);
			
			hasAlpha = CFSwapInt32LittleToHost(header->bitmaskAlpha) == true;
			mipCount = CFSwapInt32LittleToHost(header->numMipmaps);
			data = buffer + sizeof(PVRTexHeader);
		}
	}
	
	const char* data;
	uint32_t width;
	uint32_t height;
	uint32_t mipCount;
	GLenum glFormat;
	bool hasAlpha;
};

#endif
