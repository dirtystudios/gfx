//
//  MetalRenderPassCommandBuffer.mm
//  planet
//
//  Created by Eugene Sturm on 6/28/18.
//

#include "MetalRenderPassCommandBuffer.h"
#include "MetalResources.h"
#include "ResourceManager.h"
#include "MetalEnumAdapter.h"

using namespace gfx;

MetalRenderPassCommandBuffer::MetalRenderPassCommandBuffer(id<MTLRenderCommandEncoder> encoder, ResourceManager* resourceManager)
: _encoder(encoder)
, _resourceManager(resourceManager)
{
}

void MetalRenderPassCommandBuffer::setPipelineState(PipelineStateId pipelineStateId)
{
    MetalPipelineState* pipelineState = _resourceManager->GetResource<MetalPipelineState>(pipelineStateId);
    [_encoder setRenderPipelineState:pipelineState->mtlPipelineState];
    
    _currentPipelineState = pipelineState;
    
    if (pipelineState->mtlDepthStencilState) {
        [_encoder setDepthStencilState:pipelineState->mtlDepthStencilState];
    }
    [_encoder setFrontFacingWinding:MetalEnumAdapter::toMTL(pipelineState->pipelineStateDesc.rasterState.windingOrder)];
    [_encoder setCullMode:MetalEnumAdapter::toMTL(pipelineState->pipelineStateDesc.rasterState.cullMode)];
    [_encoder setTriangleFillMode:MetalEnumAdapter::toMTL(pipelineState->pipelineStateDesc.rasterState.fillMode)];
}
void MetalRenderPassCommandBuffer::setShaderBuffer(BufferId bufferId, uint8_t index, const ShaderStageFlags& stages)
{
    index += 1;
    MetalBuffer* buffer = _resourceManager->GetResource<MetalBuffer>(bufferId);
    if (stages.test(ShaderStageBitPositionVertex)) {
        [_encoder setVertexBuffer:buffer->mtlBuffer offset:0 atIndex:index];
    }
    if (stages.test(ShaderStageBitPositionPixel)) {
        [_encoder setFragmentBuffer:buffer->mtlBuffer offset:0 atIndex:index];
    }
    if (stages.test(ShaderStageBitPositionTessEval)) {
        // todo
    }
    if (stages.test(ShaderStageBitPositionTessControl)) {
        // todo
    }
}
void MetalRenderPassCommandBuffer::setShaderTexture(TextureId textureId, uint8_t index, const ShaderStageFlags& stages)
{
    MetalTexture* texture = _resourceManager->GetResource<MetalTexture>(textureId);
    if (stages.test(ShaderStageBitPositionVertex)) {
        [_encoder setVertexTexture:texture->mtlTexture atIndex:index];
        [_encoder setVertexSamplerState:texture->mtlSamplerState atIndex:index];
        
    }
    if (stages.test(ShaderStageBitPositionPixel)) {
        [_encoder setFragmentTexture:texture->mtlTexture atIndex:index];
        [_encoder setFragmentSamplerState:texture->mtlSamplerState atIndex:index];
    }
    if (stages.test(ShaderStageBitPositionTessEval)) {
        // todo
    }
    if (stages.test(ShaderStageBitPositionTessControl)) {
        // todo
    }
}
void MetalRenderPassCommandBuffer::drawIndexed(BufferId indexBufferId, uint32_t indexCount, uint32_t indexOffset, uint32_t baseVertexOffset)
{
    const MTLPrimitiveType primitiveType = MetalEnumAdapter::toMTL(_currentPipelineState->pipelineStateDesc.topology);
    MetalBuffer* indexBuffer = _resourceManager->GetResource<MetalBuffer>(indexBufferId);
    [_encoder drawIndexedPrimitives:primitiveType
                         indexCount:indexCount
                          indexType:MTLIndexTypeUInt32
                        indexBuffer:indexBuffer->mtlBuffer
                  indexBufferOffset:indexOffset * sizeof(uint32_t) // has to be in bytes when using this draw call i guess
                      instanceCount:1
                         baseVertex:baseVertexOffset
                       baseInstance:1];
}
void MetalRenderPassCommandBuffer::drawPrimitives(uint32_t startOffset, uint32_t vertexCount)
{
    const MTLPrimitiveType primitiveType = MetalEnumAdapter::toMTL(_currentPipelineState->pipelineStateDesc.topology);
    [_encoder drawPrimitives:primitiveType
                 vertexStart:startOffset
                 vertexCount:vertexCount];
    
}

void MetalRenderPassCommandBuffer::setVertexBuffer(BufferId vertexBuffer)
{
    MetalBuffer* buffer = _resourceManager->GetResource<MetalBuffer>(vertexBuffer);
    [_encoder setVertexBuffer:buffer->mtlBuffer offset:0 atIndex:0];
}

void MetalRenderPassCommandBuffer::setViewport(double originX, double originY, double width, double height)
{
    MTLViewport viewport;
    viewport.width = width;
    viewport.height = height;
    viewport.originX = originX;
    viewport.originY = originY;
    viewport.znear = 0.0;
    viewport.zfar = 1.0;
    [_encoder setViewport:viewport];
}

id<MTLRenderCommandEncoder> MetalRenderPassCommandBuffer::getMTLEncoder()
{
    return _encoder;
}
