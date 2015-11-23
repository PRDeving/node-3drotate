#include <node.h>
#include <math.h>
#include <algorithm>
#include <vector>

struct RotationAng{
    double x;
    double y;
    double z;
};

struct Point3d{
    double x;
    double y;
    double z;
};


namespace sandbox {
    using v8::Exception;
    using v8::String;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::Value;
    using v8::Array;

    void _rotate(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();

        if(args.Length() > 2){
            isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "too many args")));
            return;
        }

        Local<Array> arr = Local<Array>::Cast(args[0]);
        Local<Array> ax = Local<Array>::Cast(args[1]);

        RotationAng axrot;
        axrot.x = ax->Get(0)->NumberValue() * (M_PI/180);
        axrot.y = ax->Get(1)->NumberValue() * (M_PI/180);
        axrot.z = ax->Get(2)->NumberValue() * (M_PI/180);
    

        for(unsigned int x = 0; x < arr->Length(); x++){
            Local<Array> iarr = Local<Array>::Cast(arr->Get(x));

            Point3d Point;
            Point.x = iarr->Get(0)->NumberValue();
            Point.y = iarr->Get(1)->NumberValue();
            Point.z = iarr->Get(2)->NumberValue();

            double tx = cos(axrot.y)*Point.x + sin(axrot.y)*sin(axrot.x)*Point.y - sin(axrot.y)*cos(axrot.x)*Point.z;

            double ty = 0 + cos(axrot.x)*Point.y + sin(axrot.x)*Point.z;

            double tz = sin(axrot.y)*Point.x + cos(axrot.y)* -1*(sin(axrot.x))*Point.y + cos(axrot.y)*cos(axrot.x)*Point.z;

            iarr->Set(0,Number::New(isolate, tx));
            iarr->Set(1,Number::New(isolate, ty));
            iarr->Set(2,Number::New(isolate, tz));

            arr->Set(x,iarr);
        }

        args.GetReturnValue().Set(arr);
    }

    void Init(Local<Object> exports){
        NODE_SET_METHOD(exports, "Rotate", _rotate);
    }

    NODE_MODULE(3drotate, Init);
}
