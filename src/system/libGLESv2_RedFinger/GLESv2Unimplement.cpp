#include "ErrorLog.h"

#ifndef GL_TRUE
extern "C" {
// MaliT76x Hardware
// void glObjectPtrLabel(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetDebugMessageLog(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }

// void glBlendFunciOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendEquationiOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexBufferRangeOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexBufferOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendFuncSeparateiOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetObjectPtrLabel(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glFramebufferTextureOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }

// void glGetObjectLabel(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }

// void glGetSamplerParameterIivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDebugMessageControl(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glObjectLabel(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexParameterIivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }

// void glGetSamplerParameterIuivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glIsQueryEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetObjectPtrLabelKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetGraphicsResetStatusEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetQueryivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetTexParameterIivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetDebugMessageLogKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDisableiOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glIsEnablediOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetPointervKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glPushDebugGroupKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glSamplerParameterIuivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glColorMaskiOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetQueryObjectivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glEnableiOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glMultiTexCoord4b(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDebugMessageCallbackKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glPushDebugGroup(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glRenderbufferStorageMultisampleEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendEquationSeparateiEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetTexParameterIuivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDisableiEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetTexParameterIivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glFramebufferTextureEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexStorage3DMultisampleOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDebugMessageCallback(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendFunciEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDebugMessageInsertKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glObjectLabelKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendFuncSeparateiEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// // void glTexStorage2DEXT(){// xinjianxiaqingyuan
// // 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// // }
// void glTexBufferEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetTexParameterIuivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetnUniformivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glIsEnablediEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glObjectPtrLabelKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDeleteQueriesEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetSamplerParameterIivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexBufferRangeEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glGetObjectLabelKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glPopDebugGroup(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDebugMessageInsert(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glFramebufferTexture2DMultisampleEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendEquationSeparateiOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glSamplerParameterIivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glColorMaskiEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexParameterIivEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glBlendEquationiEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glQueryCounterEXT(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glTexParameterIuivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glDebugMessageControlKHR(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
// void glSamplerParameterIivOES(){
// 		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
// }
//-------------------------------------------------------------------------------------------
void glBeginQueryEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glBlendBarrierKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glBlendEquationSeparateiEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glBlendEquationiEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glBlendFuncSeparateiEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glBlendFunciEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glColorMaskiEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glDebugMessageCallbackKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glDebugMessageControlKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glDebugMessageInsertKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glDeleteQueriesEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glDisableiEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glEnableiEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glEndQueryEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glFramebufferTexture2DMultisampleEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glFramebufferTextureEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGenQueriesEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetDebugMessageLogKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetGraphicsResetStatusEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetObjectLabelKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetObjectPtrLabelKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetPointervKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetQueryObjecti64vEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetQueryObjectivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetQueryObjectui64vEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetQueryObjectuivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetQueryivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetSamplerParameterIivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetSamplerParameterIuivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetTexParameterIivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetTexParameterIuivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetnUniformfvEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glGetnUniformivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glIsEnablediEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glIsQueryEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glMinSampleShadingOES(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glMultiTexCoord4bOES(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glObjectLabelKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glObjectPtrLabelKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glPopDebugGroupKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glPushDebugGroupKHR(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glQueryCounterEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glReadnPixelsEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glRenderbufferStorageMultisampleEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glSamplerParameterIivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glSamplerParameterIuivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexBufferEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexBufferRangeEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexParameterIivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexParameterIuivEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexStorage2DEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexStorage3DEXT(){
		ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
void glTexStorage3DMultisampleOES(){
    ALOGD("run functionxxxxxxxxxx:%s,%d\n",__func__,__LINE__);
}
}
#endif