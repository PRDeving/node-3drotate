#WHAT IS 3DRotate?
Is a Light c++ binding that allows you to rotate a 3D mesh

After parsing your 3D object you can pass the point cloud and the angle you want to rotate and have the new position of the points as return

```javascript
var Rotate = require("3drotate");
MY_POINTS_ARRAY = Rotate.rotate(MY_POINTS_ARRAY,[ROTATION_OVER_X_AXIS, ROTATION_OVER_Y_AXIS, ROTATION_OVER_Z_AXIS]);
```

#HOW?
install with ```npm install 3drotate``` or download and build
