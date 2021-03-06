//
//  RenderBackend.h
//  planet
//
//  Created by Eugene Sturm on 6/22/18.
//

#pragma once

#include "Swapchain.h"

namespace gfx
{
    class RenderDevice;
    
    class RenderBackend
    {
    public:
        virtual ~RenderBackend() = default;
        virtual RenderDevice* getRenderDevice() = 0;
        virtual void printDeviceInfo() = 0;        
        virtual Swapchain* createSwapchainForWindow(const SwapchainDesc& swapchainDesc, RenderDevice* device, void* windowHandle) = 0;
    };
}
