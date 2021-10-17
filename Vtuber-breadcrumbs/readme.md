Tracking is based on mediapipe, to get it working this repository was immensly important: https://github.com/madelinegannon/example-mediapipe-udp

Rendering is based on diligent rendering engine, specifically on a modified gltf viewer sample.

to build the face recognition, use: bazel build -c opt --copt -DMESA_EGL_NO_X11_HEADERS --copt -DEGL_NO_X11 \
        mediapipe/examples/desktop/face_mesh:face_mesh_gpu

to run the face recognition, use: set -Ux GLOG_logtostderr 1 ; ./bazel-bin/mediapipe/examples/desktop/face_mesh/face_mesh_gpu --calculator_graph_config_file=mediapipe/graphs/face_mesh/face_mesh_desktop_live_gpu.pbtxt 
(set log probably doesn't do anything)

