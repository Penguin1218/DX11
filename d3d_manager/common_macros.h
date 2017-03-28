#pragma once
#define RETURN_ON_FAIL(hr) if(FAILED(hr)){return hr;}
#define SAFE_RELEASE(obj) if(obj){ obj->Release(); obj = NULL;}