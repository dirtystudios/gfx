//
//  MetalEnumAdapter.h
//  planet
//
//  Created by Eugene Sturm on 8/8/16.
//

#pragma once

#import <Metal/Metal.h>
#include "BlendFunc.h"
#include "BlendMode.h"
#include "CullMode.h"
#include "DGAssert.h"
#include "DepthFunc.h"
#include "FillMode.h"
#include "PixelFormat.h"
#include "PrimitiveType.h"
#include "ShaderType.h"
#include "VertexLayoutDesc.h"
#include "WindingOrder.h"
#include "StoreAction.h"
#include "LoadAction.h"
#include "TextureUsage.h"

namespace gfx {
class MetalEnumAdapter {
public:
    static MTLTextureUsage toMTL(const TextureUsageFlags& usage) {
        MTLTextureUsage mtlUsage = 0;

        if (usage.test(TextureUsageBitPositionShaderRead)) {
            mtlUsage |= MTLTextureUsageShaderRead;
        }
        
        if (usage.test(TextureUsageBitPositionShaderWrite)) {
            mtlUsage |= MTLTextureUsageShaderWrite;
        }
        
        if (usage.test(TextureUsageBitPositionRenderTarget)) {
            mtlUsage |= MTLTextureUsageRenderTarget;
        }
        
        return mtlUsage;        
    }
    
    static ShaderType fromMTL(MTLFunctionType functionType) {
        switch (functionType) {
            case MTLFunctionTypeVertex: {
                return ShaderType::VertexShader;
            }
            case MTLFunctionTypeFragment: {
                return ShaderType::PixelShader;
            }
            case MTLFunctionTypeKernel: {
                return ShaderType::ComputeShader;
            }
            default:
                dg_assert_fail_nm();
        }

        dg_assert_fail_nm();
        return ShaderType::VertexShader; // to silence warnings
    }
    static MTLVertexFormat toMTL(VertexAttributeType type, VertexAttributeStorage storage) {
        switch (type) {
            case VertexAttributeType::Float: {
                switch (storage) {
                    case VertexAttributeStorage::UInt8N:
                        dg_assert_fail_nm();
                    case VertexAttributeStorage::UInt16N:
                        dg_assert_fail_nm();
                    case VertexAttributeStorage::Float:
                        return MTLVertexFormatFloat;
                    default:
                        dg_assert_fail_nm();
                }
            }
            case VertexAttributeType::Float2: {
                switch (storage) {
                    case VertexAttributeStorage::UInt8N:
                        return MTLVertexFormatUChar2Normalized;
                    case VertexAttributeStorage::UInt16N:
                        return MTLVertexFormatUShort2Normalized;
                    case VertexAttributeStorage::Float:
                        return MTLVertexFormatFloat2;
                    default:
                        dg_assert_fail_nm();
                }
            }
            case VertexAttributeType::Float3: {
                switch (storage) {
                    case VertexAttributeStorage::UInt8N:
                        return MTLVertexFormatUChar3Normalized;
                    case VertexAttributeStorage::UInt16N:
                        return MTLVertexFormatUShort3Normalized;
                    case VertexAttributeStorage::Float:
                        return MTLVertexFormatFloat3;
                    default:
                        dg_assert_fail_nm();
                }
            }
            case VertexAttributeType::Float4: {
                switch (storage) {
                    case VertexAttributeStorage::UInt8N:
                        return MTLVertexFormatUChar4Normalized;
                    case VertexAttributeStorage::UInt16N:
                        return MTLVertexFormatUShort4Normalized;
                    case VertexAttributeStorage::Float:
                        return MTLVertexFormatFloat4;
                    default:
                        dg_assert_fail_nm();
                }
            }
            case VertexAttributeType::Int4: {
                switch (storage) {
                    case VertexAttributeStorage::UInt32N:
                        return MTLVertexFormatUInt4;
                    default:
                        dg_assert_fail_nm();
                }
            }
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLVertexFormatInvalid;
    }

    static MTLPrimitiveType toMTL(PrimitiveType type) {
        switch (type) {
            case PrimitiveType::Triangles:
                return MTLPrimitiveTypeTriangle;
            case PrimitiveType::LineStrip:
                return MTLPrimitiveTypeLineStrip;
            case PrimitiveType::Lines:
                return MTLPrimitiveTypeLine;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLPrimitiveTypeTriangle; // to silence warnings
    }

    static MTLPixelFormat toMTL(PixelFormat format) {
        switch (format) {
            case PixelFormat::R32Float:
                return MTLPixelFormatR32Float;
            case PixelFormat::RGB32Float:
                return MTLPixelFormatInvalid;
            case PixelFormat::RGBA32Float:
                return MTLPixelFormatRGBA32Float;
            case PixelFormat::R8Unorm:
                return MTLPixelFormatR8Unorm;
            case PixelFormat::RGB8Unorm:
                return MTLPixelFormatInvalid;
            case PixelFormat::RGBA8Unorm:
                return MTLPixelFormatRGBA8Unorm;
            case PixelFormat::BGRA8Unorm:
                return MTLPixelFormatBGRA8Unorm;
            case PixelFormat::Depth32Float:
                return MTLPixelFormatDepth32Float;
            case PixelFormat::Depth32FloatStencil8:
                return MTLPixelFormatDepth32Float_Stencil8;
            case PixelFormat::R8Uint:
                return MTLPixelFormatR8Uint;
            default:
                dg_assert_fail_nm();
        }
        return MTLPixelFormatInvalid;
    }
    
    static PixelFormat fromMTL(MTLPixelFormat format) {
        switch (format) {
            case MTLPixelFormatR32Float:
                return PixelFormat::R32Float;
            case MTLPixelFormatRGBA32Float:
                return PixelFormat::RGBA32Float;
            case MTLPixelFormatR8Unorm:
                return PixelFormat::R8Unorm;            
            case MTLPixelFormatRGBA8Unorm:
                return PixelFormat::RGBA8Unorm;
            case MTLPixelFormatBGRA8Unorm:
                return PixelFormat::BGRA8Unorm;
            case MTLPixelFormatDepth32Float:
                return PixelFormat::Depth32Float;
            case MTLPixelFormatDepth32Float_Stencil8:
                return PixelFormat::Depth32FloatStencil8;
            case MTLPixelFormatInvalid:
                return PixelFormat::Invalid;
            default:
                // oops
                return PixelFormat::Invalid;
        }
        return PixelFormat::Invalid;
    }

    static MTLBlendOperation toMTL(BlendMode mode) {
        switch (mode) {
            case BlendMode::Add:
                return MTLBlendOperationAdd;
            case BlendMode::Subtract:
                return MTLBlendOperationSubtract;
            case BlendMode::ReverseSubtract:
                return MTLBlendOperationReverseSubtract;
            case BlendMode::Min:
                return MTLBlendOperationMin;
            case BlendMode::Max:
                return MTLBlendOperationMax;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLBlendOperationAdd;
    }

    static MTLBlendFactor toMTL(BlendFunc func) {
        switch (func) {
            case BlendFunc::Zero:
                return MTLBlendFactorZero;
            case BlendFunc::One:
                return MTLBlendFactorOne;
            case BlendFunc::SrcColor:
                return MTLBlendFactorSourceColor;
            case BlendFunc::OneMinusSrcColor:
                return MTLBlendFactorOneMinusSourceColor;
            case BlendFunc::SrcAlpha:
                return MTLBlendFactorSourceAlpha;
            case BlendFunc::OneMinusSrcAlpha:
                return MTLBlendFactorOneMinusSourceAlpha;
            case BlendFunc::DstAlpha:
                return MTLBlendFactorDestinationAlpha;
            case BlendFunc::OneMinusDstAlpha:
                return MTLBlendFactorOneMinusDestinationAlpha;
            case BlendFunc::ConstantColor:
            case BlendFunc::OneMinusConstantColor:
            case BlendFunc::ConstantAlpha:
            case BlendFunc::OneMinusConstantAlpha:
                dg_assert_fail_nm();
            case BlendFunc::SrcAlphaSaturate:
                return MTLBlendFactorSourceAlphaSaturated;
            case BlendFunc::Src1Color:
                return MTLBlendFactorBlendColor;
            case BlendFunc::OneMinusSrc1Color:
                return MTLBlendFactorOneMinusBlendColor;
            case BlendFunc::Src1Alpha:
                return MTLBlendFactorBlendAlpha;
            case BlendFunc::OneMinusSrc1Alpha:
                return MTLBlendFactorOneMinusBlendAlpha;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLBlendFactorZero;
    }

    static MTLCullMode toMTL(CullMode mode) {
        switch (mode) {
            case CullMode::None:
                return MTLCullModeNone;
            case CullMode::Front:
                return MTLCullModeFront;
            case CullMode::Back:
                return MTLCullModeBack;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLCullModeNone;
    }

    static MTLWinding toMTL(WindingOrder mode) {
        switch (mode) {
            case WindingOrder::FrontCCW:
                return MTLWindingCounterClockwise;
            case WindingOrder::FrontCW:
                return MTLWindingClockwise;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLWindingCounterClockwise;
    }

    static MTLTriangleFillMode toMTL(FillMode mode) {
        switch (mode) {
            case FillMode::Solid:
                return MTLTriangleFillModeFill;
            case FillMode::Wireframe:
                return MTLTriangleFillModeLines;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLTriangleFillModeFill;
    }

    static MTLCompareFunction toMTL(DepthFunc func) {
        switch (func) {
            case DepthFunc::Never:
                return MTLCompareFunctionNever;
            case DepthFunc::Less:
                return MTLCompareFunctionLess;
            case DepthFunc::Equal:
                return MTLCompareFunctionEqual;
            case DepthFunc::LessEqual:
                return MTLCompareFunctionLessEqual;
            case DepthFunc::Greater:
                return MTLCompareFunctionGreater;
            case DepthFunc::NotEqual:
                return MTLCompareFunctionNotEqual;
            case DepthFunc::GreaterEqual:
                return MTLCompareFunctionGreaterEqual;
            case DepthFunc::Always:
                return MTLCompareFunctionAlways;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLCompareFunctionNever;
    }
    
    static MTLStoreAction toMTL(StoreAction storeAction) {
        switch (storeAction) {
            case StoreAction::DontCare:
                return MTLStoreActionDontCare;
            case StoreAction::Store:
                return MTLStoreActionStore;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLStoreActionDontCare;
    }
    
    static MTLLoadAction toMTL(LoadAction loadAction) {
        switch (loadAction) {
            case LoadAction::DontCare:
                return MTLLoadActionDontCare;
            case LoadAction::Load:
                return MTLLoadActionLoad;
            case LoadAction::Clear:
                return MTLLoadActionClear;
            default:
                dg_assert_fail_nm();
        }
        dg_assert_fail_nm();
        return MTLLoadActionDontCare;
    }
};
}
