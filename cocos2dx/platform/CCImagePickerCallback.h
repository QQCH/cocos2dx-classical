/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-better
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __CCImagePickerCallback__
#define __CCImagePickerCallback__

#include "ccTypes.h"

using namespace std;

NS_CC_BEGIN

/// interface of CCImagePicker event
class CC_DLL CCImagePickerCallback {
public:
	/**
	 * Invoked when image is picked
	 *
	 * @param fullPath the picked image is saved into an image file, and this is image file absolute path
	 * @param w image width in pixel
	 * @param h image height in pixel
	 */
	virtual void onImagePicked(const string& fullPath, int w, int h) = 0;
	
	/**
	 * invoked when image picking cancelled
	 */
	virtual void onImagePickingCancelled() = 0;
};

NS_CC_END

#endif // __CCImagePickerCallback__
